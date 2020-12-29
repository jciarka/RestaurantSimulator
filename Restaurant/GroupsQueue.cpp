#include "GroupsQueue.h"
#include "ITable.h"

GroupQueue::GroupQueue(std::vector<ITable*>* restaurant_tables, ITrigger* global_trigger, IRaporter* global_raporter)
                       : Triggered(global_trigger), Raportable(global_raporter), tables(restaurant_tables)
{
}

void GroupQueue::add_group(std::unique_ptr<IGroup> group)
{
    groups.push_back(std::move(group));
}

void GroupQueue::execute_iteration()
{
	for (auto group = groups.begin(); group != groups.end(); ++group)
	{
		for (auto table : *tables)
		{			
			if (table->can_place_group(group->get()))
			{
				table->place_group(std::move(*group));
				*group = nullptr;
				break;
			}
		}
	}

	groups.erase(std::remove(groups.begin(), groups.end(), nullptr), groups.end());
}
