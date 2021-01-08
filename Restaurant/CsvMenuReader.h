#pragma once
#include <vector>
#include "DishBase.h"
#include "IMenu.h"
#include <fstream>

class CsvMenuReader
{
private:
	ITrigger* global_trigger_ptr;
	IRaporter* global_raporter_ptr;
public:
	CsvMenuReader(ITrigger* global_trigger_ptr, IRaporter* global_raporter_ptr);
	std::vector<std::string> readthefile(std::string filename);
};
