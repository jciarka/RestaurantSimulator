#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "Trigger.h"
#include "TerminalRaporter.h"
#include "StandardClient.h"
#include "HungryClient.h"
#include "DessertLovingClient.h"
#include "HungryDessertLovingClient.h"
#include "TestGroup.h"
#include "ServiceQueue.h"
#include "Group.h"
#include "GroupsQueue.h"

class GroupGenerator : public Triggered, public Raportable
{
private:
	IServiceQueue* service_queue;
	ITrigger* global_trigger;
	IRaporter* global_raporter;
	GroupQueue& groups_queue_ref;
	std::vector<unsigned> odds;
public:
	GroupGenerator(std::vector<unsigned> odds, GroupQueue& groups_queue_ref, IServiceQueue* service_queue, ITrigger* global_trigger, IRaporter* global_raporter);
	virtual void execute_iteration() override;
	void generate_group();
};
