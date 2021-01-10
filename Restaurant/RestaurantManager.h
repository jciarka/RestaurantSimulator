#pragma once
#include "Trigger.h"
#include "CombinedRaporter.h"
#include "Menu.h"
#include "Table.h"
#include "Waiter.h"
#include "Kitchen.h"
#include "ServiceQueue.h"
#include "GroupGenerator.h"
#include <chrono>
#include <random>


class RestaurantManager
{
private:
	Trigger trigger;
	CombinedRaporter raporter;
	Kitchen kitchen;
	size_t interation_number;
	ServiceQueue servicequeue;
	GroupQueue groups_queue;
	Menu* menu_ptr;
	GroupGenerator* generator_ptr;
	std::vector<ITable*> tables;
	std::vector<Waiter*> waiters;

public:
	RestaurantManager(std::string soupcsv, std::string maincoursecsv, std::string dessertcsv, std::string beveragecsv, std::string tablecsv, std::string numer_of_waiters, std::string oddscsv);
	void execute_iteration();
	~RestaurantManager();
};