#include "Group.h"
#include "ITable.h"
#include "IServiceQueue.h"
#include <sstream>


// ______________________________________________________________________________________________________
// Cz�� statyczna
unsigned Group::id_counter = 0; // Inicjacja pocz�tkowej wartosci od kt�rej nadawane b�dzie id

unsigned Group::generate_unique_id()
{
	return ++id_counter;
}
// ______________________________________________________________________________________________________

Group::Group(bool waiting_for_friends, IServiceQueue* service_queue,
	         ITrigger* global_trigger, IRaporter* global_raporter)
	          : Triggered(global_trigger), Raportable(global_raporter),
				id(generate_unique_id()), service_queue(service_queue)
{
	if (waiting_for_friends)
	{
		state = IClient::client_state::WAITING_FOR_FRIENDS;
	}
	else
	{
		state = IClient::client_state::READY_TO_BEGIN;
	}
}

unsigned Group::get_id() const
{
	return id;
}

std::vector<IClient*> Group::get_clients() const
{
	return clients; // copy of vector
}

ITable* Group::get_table() const
{
	return table;
}


unsigned Group::get_members_num() const
{
	return clients.size();
}


void Group::add_client(IClient* client)
{
	if (!(state == IClient::client_state::WAITING_FOR_FRIENDS || state == IClient::client_state::READY_TO_BEGIN) 
		|| table != nullptr)
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group " << id << ": add_client called not on an initiation step";
		throw std::logic_error(error_txt_stream.str());
	}

	if(client == nullptr)
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group " << id << ": add_client called with nullpointer to client as parameter";
		throw std::logic_error(error_txt_stream.str());
	}

	clients.push_back(client);
	client->set_group(this);
}


std::vector<IClient*> Group::remove_clients()
{
	if (!(state == IClient::client_state::WAITING_FOR_FRIENDS || state == IClient::client_state::READY_TO_BEGIN))
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group " << id << ": remove_clients called when clients are not WAITING_FOR_FRIENDS or READY_TO_BEGIN";
		throw std::logic_error(error_txt_stream.str());
	}

	// Po scaleniu do innej grupy trzeba usun�� z tego obiektu wszyskich kilient�w,
	// Je�li tego nie zrobimy w po usunieciu tego obiektu zniszczymy kliet�w, 
	// chocia� b�d� logicznie w innej grupie

	std::vector<IClient*> temp = clients;
	clients.clear();
	return clients;
}

void Group::seat_at_table(ITable* table)
{
	if (table == nullptr)
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group " << id << ": set_table called with null pointer parameter";
		throw std::logic_error(error_txt_stream.str());
	}
	this->table = table;

	// Je�li w stanie READY_TO_BEGIN rozpocznij uczt�
	if (get_state() == IClient::client_state::READY_TO_BEGIN)
	{
		begin_feast();
	}
	// Je�li w stanie WAITING_FOR_FRIENDS grupa oczekuje przy stole
}

void Group::begin_feast()
{
	for (auto client : clients)
	{
		client->begin_feast();
	}
}

void Group::merge(IGroup* group)
{
	std::stringstream error_txt_stream;
	if (state != IClient::client_state::WAITING_FOR_FRIENDS)
	{
		error_txt_stream << "Group " << id << ": can't marge with other group when not waiting for friends";
		throw std::logic_error(error_txt_stream.str());
	}

	if (group == nullptr)
	{
		error_txt_stream << "Group " << id << ": merge_group called with null pointer parameter";
		throw std::logic_error(error_txt_stream.str());
	}

	if (!(group->get_state() == IClient::client_state::READY_TO_BEGIN || group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS))
	{
		error_txt_stream << "Group " << id << ": merge_group called with already eating group";
		throw std::logic_error(error_txt_stream.str());
	}

	// Przenie� klietn�w
	for (auto client : group->remove_clients())
	{
		client->set_group(this);
		clients.push_back(client);
	}
	// Zaktualizuj stan grupy
	state = group->get_state();
	// Usu� do��czan� grup�
	delete group;

	if (state == IClient::client_state::READY_TO_BEGIN)
	{
		begin_feast();
	}
	// je�eli state == IClient::client_state::WAITING_FOR_FRIENDS
	// to oznacza, �e nadal nie wszystkie osoby przyby�y
}

IClient::client_state Group::get_state() const
{
	return state;
}


void Group::on_client_state_changed(IClient* clinet)
{
	// Sprawd� czy stan wszystkich klient�w o jeden wi�kszy ni� grupy
	// Je�li tak to zmie� stan grupy
	for (auto client : clients)
	{
		if ( static_cast<int>(client->get_state()) != static_cast<int>(state) + 1 )
		{
			return;
		}
	}
	
	// Zmie� stan
	state = static_cast<IClient::client_state>(static_cast<int>(state) + 1);

	// Wykonaj operacje
	std::ostringstream raport_stream;
	switch (state)
	{

	case IClient::client_state::WAITING_FOR_CARD:
		raport_stream << "Table: " << table->get_id() <<
			             " Group: " << id << " Calls waiter for menu";
		raport(raport_stream.str());
		// Wezwij kelnera z menu
		service_queue->queue_service(this);
		break;

	case IClient::client_state::CHOOSING_DISHES:
		break;

	case IClient::client_state::READY_TO_ORDER:
		raport_stream << "Table: " << table->get_id() <<
			             " Group: " << id << " Calls waiter to order";
		raport(raport_stream.str());
		// Wezwij kelnera aby zam�wi�
		service_queue->queue_service(this);
		break;

	case IClient::client_state::WAITING_FOR_DISHES:
		break;

	case IClient::client_state::EATING:
		break;

	case IClient::client_state::FINISHED_EATING:
		raport_stream << "Table: " << table->get_id() <<
			             " Group: " << id << " Calls waiter to pay";
		raport(raport_stream.str());
		// Wezwij kelnera aby zap�aci�
		service_queue->queue_service(this);
		break;

	case IClient::client_state::LEAVING:
		raport_stream << "Table: " << table->get_id() <<
			             " Group: " << id << " Is preparing to leave";
		raport(raport_stream.str());
		// Powiadom stolik �e gotowa do wyj�cia
		table->on_group_state_change(this);
		break;

	default:
		break;
	};
}

Group::~Group()
{
	for (auto client : clients)
	{
		if (client != nullptr)
		{
			delete client;
			client = nullptr;
		}
	}
}
