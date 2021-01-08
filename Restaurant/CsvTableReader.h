#pragma once
#include <vector>
#include <string>

class CsvTableReader
{
private:
	std::vector<unsigned> table_sizes;
public:
	CsvTableReader() {};
	std::vector<unsigned> readthefile(std::string filename);
};
