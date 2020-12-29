#pragma once

#include "fwd_include.h"
#include "IGroup.h"
#include "ITable.h"

#include <vector>
#include <list>

class GroupQueue : public Triggered, public Raportable
{
private:
	std::vector<std::unique_ptr<IGroup> > groups;
	std::vector<ITable*>* tables;

public:
	GroupQueue(std::vector<ITable*>* restaurant_tables, ITrigger* global_trigger, IRaporter* global_raporter);

	void add_group(std::unique_ptr<IGroup> group);
	void execute_iteration() override;
};