#include "RestaurantManager.h"
#include "CsvMenuReader.h"
#include "CsvTableReader.h"
#include "CsvGeneratorReader.h"
#include <chrono>
#include <thread>

RestaurantManager::RestaurantManager(std::string soupcsv, std::string maincoursecsv, std::string dessertcsv, std::string beveragecsv, std::string tablecsv, std::string numer_of_waiters, std::string oddscsv)
	: kitchen(&raporter), servicequeue(&raporter), groups_queue(&tables, &trigger, &raporter)
{
	interation_number = 0;
	CsvMenuReader csvmenureader;
	std::vector<std::string> SoupArguments = csvmenureader.readthefile(soupcsv);
	std::vector<std::string> MainCourseArguments = csvmenureader.readthefile(maincoursecsv);
	std::vector<std::string> DessertArguments = csvmenureader.readthefile(dessertcsv);
	std::vector<std::string> BeverageArguments = csvmenureader.readthefile(beveragecsv);
	menu_ptr = new Menu(SoupArguments, MainCourseArguments, DessertArguments, BeverageArguments, &trigger, &raporter);
	CsvTableReader csvtablereader;
	std::vector<unsigned> table_sizes = csvtablereader.readthefile(tablecsv);
	
	for (int i = 0; i < table_sizes.size(); i++)
	{
		tables.push_back(new Table(table_sizes[i], &trigger, &raporter));
	};
	unsigned uns_numer_of_waiters = std::stoul(numer_of_waiters, nullptr, 10);
	if(uns_numer_of_waiters == 0)
	{
		waiters.push_back(new Waiter(menu_ptr, &kitchen, &servicequeue, &trigger, &raporter));
	}
	for (int i = 0; i < uns_numer_of_waiters; i++)
	{
		waiters.push_back(new Waiter(menu_ptr, &kitchen, &servicequeue, &trigger, &raporter));
	};
	CsvGeneratorReader csvgeneratorreader;
	std::vector<unsigned> odds = csvgeneratorreader.readthefile(oddscsv);
	generator_ptr = new GroupGenerator(odds, groups_queue, &servicequeue, &trigger, &raporter);

}

void RestaurantManager::execute_iteration()
{
	trigger.execute_iteration();
	std::stringstream info;
	info << std::endl << "---------------------------------------iter" << interation_number++ << std::endl;
	raporter.raport(info.str());
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}


RestaurantManager::~RestaurantManager()
{
	for (int i = 0; i < tables.size(); i++)
	{
		delete tables[i];
	};

	for (int i = 0; i < waiters.size(); i++)
	{
		delete waiters[i];
	};

	delete menu_ptr;
	delete generator_ptr;
}
