#include "Table.h"
#include <sstream>

// ______________________________________________________________________________________________________
// Cz�� statyczna
unsigned Table::id_counter = 0; // Inicjacja pocz�tkowej wartosci od kt�rej nadawane b�dzie id

unsigned Table::generate_unique_id()
{
	return ++id_counter;
}
// ______________________________________________________________________________________________________


Table::Table(unsigned seats_num, ITrigger& global_trigger, IRaporter& global_raporter) 
	         : Triggered(global_trigger), Raportable(global_raporter), id(generate_unique_id()),
			   seats_number(seats_num), group(nullptr), group_preapring_to_leave(false)
{
}

unsigned Table::get_id() const
{
    return 0;
}

bool Table::is_available() const
{
	if (group == nullptr)
	{
		return true;
	}

	if (group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		return true;
	}

	return false;
}

unsigned Table::get_empty_seats() const
{
	if (group == nullptr)
	{
		return seats_number;
	}

	if (group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		return seats_number - group->get_members_num();
	}

	// Zwr�� 0 gdy grupa ju� przypisana do stolika, ale jest winnym stanie ni� WAITING_FOR_FRIENDS
	return 0;
}


bool Table::can_place_group(IGroup* group) const
{
	if (group == nullptr)
	{
		return false;
	}

	// Sprawd� czy dodawana grupa jest w odpowiedim stanie oraz czy jest odpowiednia liczba miejsc przy stole
	if (group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		// Je�li grupa jest typu WAITING_FOR_FRIENDS przynajmniej jedno miejsce musi zostac wolne
		if (group->get_members_num() < get_empty_seats())
			return true;
	}
	else if (group->get_state() == IClient::client_state::READY_TO_BEGIN)
	{
		// Mo�na zaj�c wszytkie wolne miejsca
		if (group->get_members_num() <= get_empty_seats())
			return true;
	}

	// Je�li niewystarczaj�ca liczba miejsc lub grupa w innym stanie zwr�� false 
	return false;
}


void Table::place_group(IGroup* group)
{
	if (!can_place_group(group))
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group is invalid to be posed at table: " << id;
		throw std::logic_error(error_txt_stream.str());
	}

	if (this->group == nullptr)
	{
		// Powi�� grup� i stolik
		this->group = group;
		group->seat_at_table(this);
	}
	else if (this->group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		// Po��cz grup� z istniej�ca grup�
		this->group->merge(group);
	}
	else
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group " << id << ": can't marge with other group when"
			<< " it is not waiting for friends or ready to eat";
		throw std::logic_error(error_txt_stream.str());
	}
}


void Table::on_group_state_change(IGroup* group)
{
	if (group->get_state() == IClient::client_state::LEAVING)
	{
		group_preapring_to_leave = true;
	}
}

void Table::execute_iteration()
// Grupa kiedy opuszcza lokal nastawia group_preapring_to_leave
// Nale�y tak� grup� usun��, ale nie mo�na tego zrobi� bezpo�redio 
// w on_group_state_change wywo��nej przez t� grup�
{
	if (group_preapring_to_leave)
	{
		std::stringstream raport_stream;
		raport_stream << "Table: " << get_id() <<
			             " Group " << group->get_id() << " has left restaurant";
		raport(raport_stream.str());

		// usu� grup�
		delete group;
		group = nullptr;
		group_preapring_to_leave = false;

	}
}

Table::~Table()
{
	if (group != nullptr)
	{
		delete group;
	}
}
