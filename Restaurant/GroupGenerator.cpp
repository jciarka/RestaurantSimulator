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
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	const unsigned client_types = 4;
	std::mt19937 generator(seed);
	bool waiting_for_friends = false;
	if (generator() % odds[0] == 0)
	{
		if (generator() % odds[1] == 0);
		{
			bool waiting_for_friends = true;
		}
		std::unique_ptr<IGroup> group{ new Group(waiting_for_friends, service_queue, global_trigger, global_raporter) };
		bool group_is_empty = true;
		for (int i = 0; i < generator() % odds[2]; i++)
		{
			std::unique_ptr<IClient> client = std::make_unique<StandardClient>(generator() % odds[3], global_trigger, global_raporter);
			group->add_client(std::move(client));
			group_is_empty = false;
		}
		for (int i = 0; i < generator() % odds[4]; i++)
		{
			std::unique_ptr<IClient> client = std::make_unique<HungryClient>(generator() % odds[5], global_trigger, global_raporter);
			group->add_client(std::move(client));
			group_is_empty = false;
		}
		for (int i = 0; i < generator() % odds[6]; i++)
		{
			std::unique_ptr<IClient> client = std::make_unique<HungryDessertLovingClient>(generator() % odds[7], global_trigger, global_raporter);
			group->add_client(std::move(client));
			group_is_empty = false;
		}
		for (int i = 0; i < generator() % odds[8]; i++)
		{
			std::unique_ptr<IClient> client = std::make_unique<DessertLovingClient>(generator() % odds[9], global_trigger, global_raporter);
			group->add_client(std::move(client));
			group_is_empty = false;
		}
		if (group_is_empty)
		{
			if (generator() % client_types == 0)
			{
				std::unique_ptr<IClient> client = std::make_unique<StandardClient>(generator() % odds[3], global_trigger, global_raporter);
				group->add_client(std::move(client));
			}
			if (generator() % client_types == 1)
			{
				std::unique_ptr<IClient> client = std::make_unique<HungryClient>(generator() % odds[5], global_trigger, global_raporter);
				group->add_client(std::move(client));
			}
			if (generator() % client_types == 2)
			{
				std::unique_ptr<IClient> client = std::make_unique<HungryDessertLovingClient>(generator() % odds[7], global_trigger, global_raporter);
				group->add_client(std::move(client));
			}
			else
			{
				std::unique_ptr<IClient> client = std::make_unique<DessertLovingClient>(generator() % odds[9], global_trigger, global_raporter);
				group->add_client(std::move(client));
			}
		}
		groups_queue_ref.add_group(std::move(group));
	}
};
