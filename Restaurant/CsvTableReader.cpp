#include "CsvTableReader.h"
#include "Triggered.h"
#include "Raportable.h"
#include <fstream>
#include <string>



std::vector<unsigned> CsvTableReader::readthefile(std::string filename)
{
	std::ifstream tablecsv;
	tablecsv.open(filename);
	while (tablecsv.good())
	{
		std::string table_size;
		getline(tablecsv, table_size, ',');
		unsigned table_size_uns = std::stoul(table_size, nullptr, 10);
		table_sizes.push_back(table_size_uns);
	}
	tablecsv.close();
	return table_sizes;
};