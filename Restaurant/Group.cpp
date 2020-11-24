#include "Group.h"

/*
// ______________________________________________________________________________________________________
// Czêœæ statyczna
unsigned Group::id_counter = 0; // Inicjacja pocz¹tkowej wartosci od której nadawane bêdzie id

unsigned Group::generate_unique_id()
{
	return ++id_counter;
}
// ______________________________________________________________________________________________________


StandardClient::StandardClient(unsigned choosing_time, IGroup* group, ITable* table,
							   ITrigger& global_trigger, IRaporter& global_raporter)
	: TriggeredCounter(global_trigger), Raportable(global_raporter), choosing_time(choosing_time),
	  group(group), table(table), state(IClient::client_state::WAITING_FOR_FRIENDS), menu(nullptr),
	  id(generate_unique_id())
{
	// dishes is empty at the beginning
}
*/
/*
Group::Group(bool waiting_for_friends, ITrigger& global_trigger, IRaporter& global_raporter)\
	: TriggeredCounter(global_trigger), Raportable(global_raporter)
{
	if (wait)
	{

	}
}

unsigned Group::get_id() const
{
	return 0;
}

std::vector<IClient*> Group::give_clients()
{
	return std::vector<IClient*>();
}

void Group::on_client_state_changed(IClient* clinet)
{
}

unsigned Group::get_members_num()
{
	return 0;
}

unsigned Group::merge(IGroup* group)
{
	return 0;
}

IClient::client_state Group::get_group_state()
{
	return IClient::client_state();
}

Group::~Group()
{
	for (auto client : clients)
	{
		delete client;
		client = nullptr;
	}
}
*/