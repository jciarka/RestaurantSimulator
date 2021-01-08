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

void test5(std::string filename0, std::string filename1, std::string filename2, std::string filename3, std::string filename4, std::string numer_of_waiters, std::string filename5)
{
	Trigger trigger;
	TerminalRaporter raporter;
	Kitchen kitchen(&raporter);
	ServiceQueue servicequeue(&raporter);
	CsvMenuReader CsvReader(&trigger, &raporter);
	std::vector<std::string> SoupArguments = CsvReader.readthefile(filename0);
	std::vector<std::string> MainCourseArguments = CsvReader.readthefile(filename1);
	std::vector<std::string> DessertArguments = CsvReader.readthefile(filename2);
	std::vector<std::string> BeverageArguments = CsvReader.readthefile(filename3);
	Menu menu(SoupArguments, MainCourseArguments, DessertArguments, BeverageArguments, &trigger, &raporter);
	CsvTableReader csvtablereader;
	std::vector<unsigned> table_sizes = csvtablereader.readthefile(filename4);
	std::vector<ITable*> tables;
	for (int i = 0; i < table_sizes.size(); i++)
	{
		tables.push_back(new Table(table_sizes[i], &trigger, &raporter));
	};
	unsigned uns_numer_of_waiters = std::stoul(numer_of_waiters, nullptr, 10);
	
	for (int i = 0; i < uns_numer_of_waiters; i++)
	{
		Waiter waiter(&menu, &kitchen, &servicequeue, &trigger, &raporter);
	};
	GroupQueue groups_queue(&tables, &trigger, &raporter);
	CsvGeneratorReader csvgeneratorreader;
	std::vector<unsigned> odds = csvgeneratorreader.readthefile(filename5);
	GroupGenerator groupgenerator(odds, groups_queue, &servicequeue, &trigger, &raporter);
};
