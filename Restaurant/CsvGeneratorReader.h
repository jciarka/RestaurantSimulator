#pragma once
#include <vector>
#include <string>

class CsvGeneratorReader
{
private:
	std::vector<unsigned> odds;
public:
	CsvGeneratorReader() {};
	std::vector<unsigned> readthefile(std::string filename);
};

