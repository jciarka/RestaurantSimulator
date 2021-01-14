#include "GroupGenerator.h"
#include "Group.h"
#include <chrono>
#include <random>


GroupGenerator::GroupGenerator(std::vector<unsigned> odds, GroupQueue& groups_queue_ref, IServiceQueue* service_queue, ITrigger* global_trigger, IRaporter* global_raporter)
	: Triggered(global_trigger), Raportable(global_raporter), groups_queue_ref(groups_queue_ref), service_queue(service_queue), global_trigger(global_trigger), global_raporter(global_raporter), odds(odds)
{
}

void GroupGenerator::execute_iteration()
{
	generate_group();
};

void GroupGenerator::generate_group()
// odds is loaded from a csv file, first argument is the odds of generating a group in one trigger (the odds are 1/x)
// second argument is the odds of the group waiting for friends (1/x)
// third argument is the maximum amount of StandardClients in a group (odds of each possible amount of clients is equal to 1/x)
// fourth argument is the maximum amount of time a StandardClient will choose his meal (odds of each possible waiting time is equal to 1/x)
// fifth argument is the maximum amount of HungryClients in a group (odds of each possible amount of clients is equal to 1/x)
// sixth argument is the maximum amount of time a HungryClient will choose his meal (odds of each possible waiting time is equal to 1/x)
// seventh argument is the maximum amount of HungryDessertLovingClients in a group (odds of each possible amount of clients is equal to 1/x)
// eigth argument is the maximum amount of time a HungryDessertLovingClient will choose his meal (odds of each possible waiting time is equal to 1/x)
// ninegth argument is the maximum amount of DessertLovingClients in a group (odds of each possible amount of clients is equal to 1/x)
// tength argument is the maximum amount of time a DessertLovingClient will choose his meal (odds of each possible waiting time is equal to 1/x)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	const unsigned client_types = 4;
	std::mt19937 generator(seed);
	bool waiting_for_friends = false;
	if (generator() % odds[0] == 0)
	{
		if (generator() % odds[1] == 0)
		{
			waiting_for_friends = true;
		}
		std::unique_ptr<IGroup> group{ new Group(waiting_for_friends, service_queue, global_trigger, global_raporter) };
		bool group_is_empty = true;
		for (int i = 0; i < generator() % odds[2]; i++)
		{
			std::unique_ptr<IClient> client = std::make_unique<StandardClient>(generator() % odds[3] + 1, global_trigger, global_raporter);
			group->add_client(std::move(client));
			group_is_empty = false;
		}
		for (int i = 0; i < generator() % odds[4]; i++)
		{
			std::unique_ptr<IClient> client = std::make_unique<HungryClient>(generator() % odds[5] + 1, global_trigger, global_raporter);
			group->add_client(std::move(client));
			group_is_empty = false;
		}
		for (int i = 0; i < generator() % odds[6]; i++)
		{
			std::unique_ptr<IClient> client = std::make_unique<HungryDessertLovingClient>(generator() % odds[7] + 1, global_trigger, global_raporter);
			group->add_client(std::move(client));
			group_is_empty = false;
		}
		for (int i = 0; i < generator() % odds[8]; i++)
		{
			std::unique_ptr<IClient> client = std::make_unique<DessertLovingClient>(generator() % odds[9] + 1, global_trigger, global_raporter);
			group->add_client(std::move(client));
			group_is_empty = false;
		}
		// Group is already being generated so it needs at least one client, this increases the odds of having a single client in a group sliglty
		if (group_is_empty)
		{
			int random_number_between_0_and_3 = generator() % client_types;
			if (random_number_between_0_and_3 == 0)
			{
				std::unique_ptr<IClient> client = std::make_unique<StandardClient>(generator() % odds[3] + 1, global_trigger, global_raporter);
				group->add_client(std::move(client));
			}
			if (random_number_between_0_and_3 == 1)
			{
				std::unique_ptr<IClient> client = std::make_unique<HungryClient>(generator() % odds[5] + 1, global_trigger, global_raporter);
				group->add_client(std::move(client));
			}
			if (random_number_between_0_and_3 == 2)
			{
				std::unique_ptr<IClient> client = std::make_unique<HungryDessertLovingClient>(generator() % odds[7] + 1, global_trigger, global_raporter);
				group->add_client(std::move(client));
			}
			if (random_number_between_0_and_3 == 3)
			{
				std::unique_ptr<IClient> client = std::make_unique<DessertLovingClient>(generator() % odds[9] + 1, global_trigger, global_raporter);
				group->add_client(std::move(client));
			}
		}
		groups_queue_ref.add_group(std::move(group));
	}
};
