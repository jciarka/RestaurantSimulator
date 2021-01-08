#include "CsvMenuReader.h"
#include "Triggered.h"
#include "Raportable.h"

#include <string>


CsvMenuReader::CsvMenuReader(ITrigger* global_trigger_ptr, IRaporter* global_raporter_ptr) 
{
	this->global_trigger_ptr = global_trigger_ptr;
	this->global_raporter_ptr = global_raporter_ptr;
};

std::vector<std::string> CsvMenuReader::readthefile(std::string filename)
{
	std::ifstream menucsv;
	std::vector<std::string> dish_arguments;
	menucsv.open(filename);
	while (menucsv.good())
	{
		std::string prepraring_time;
		std::getline(menucsv, prepraring_time, ',');
		
		std::string eating_time;
		std::getline(menucsv, eating_time, ',');
		
		std::string name;
		std::getline(menucsv, name, ',');

		std::string dish_price;
		std::getline(menucsv, dish_price, '\n');
		
		dish_arguments.push_back(prepraring_time);
		dish_arguments.push_back(eating_time);
		dish_arguments.push_back(name);
		dish_arguments.push_back(dish_price);
	}
	menucsv.close();
	return dish_arguments;
}
