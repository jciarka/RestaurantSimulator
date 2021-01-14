#pragma once
#include <vector>
#include "DishBase.h"
#include "IMenu.h"
#include <fstream>

class CsvMenuReader
{
public:
	CsvMenuReader() {};
	std::vector<std::string> readthefile(std::string filename);
};
