#pragma once
#include "Tests.h"
#include "CsvMenuReader.h"
#include "Trigger.h"
#include "TerminalRaporter.h"
#include "Menu.h"
#include "Table.h"
#include "CsvTableReader.h"
#include "Waiter.h"
#include "Kitchen.h"
#include "ServiceQueue.h"
#include "CsvGeneratorReader.h"
#include "GroupGenerator.h"
#include <chrono>
#include <random>

class RestaurantManager
{
private:
	Trigger trigger;
	TerminalRaporter raporter;
	Kitchen kitchen;
	ServiceQueue servicequeue;
	CsvMenuReader CsvMenuReader;
	Menu menu;
	CsvTableReader csvtablereader;
	std::vector<ITable*> tables;
	GroupQueue groups_queue;
	CsvGeneratorReader csvgeneratorreader;
	GroupGenerator groupgenerator;
public:
	RestaurantManager();
};