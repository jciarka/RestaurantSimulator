#include "CsvTableReader.h"
#include "Triggered.h"
#include "Raportable.h"
#include <fstream>
#include <sstream>
#include <string>



std::vector<unsigned> CsvTableReader::readthefile(std::string filename)
{
	std::ifstream tablecsv;
	tablecsv.open(filename);
	if (!(tablecsv.is_open()))
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "File: " << filename << " could not be opened";
		throw std::invalid_argument(error_txt_stream.str());
	}
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