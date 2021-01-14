#include "CsvMenuReader.h"
#include "Triggered.h"
#include "Raportable.h"
#include <sstream>
#include <string>



std::vector<std::string> CsvMenuReader::readthefile(std::string filename)
{
	std::ifstream menucsv;
	std::vector<std::string> dish_arguments;
	menucsv.open(filename);
	if (!(menucsv.is_open()))
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "File: " << filename << " could not be opened";
		throw std::invalid_argument(error_txt_stream.str());
	}
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
	bool valid = true;
	for(int i = 0; i < dish_arguments.size(); i++)
	{
		if(dish_arguments[i] == "")
		{
			valid = false;
		}
	}
	if (valid == false)
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "File: " << filename << " contains wrong amount of arguments, the number of arguments needs to be divisible by 4.";
		throw std::logic_error(error_txt_stream.str());
	}
	return dish_arguments;
}
