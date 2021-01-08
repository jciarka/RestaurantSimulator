#include "CsvGeneratorReader.h"
#include "Triggered.h"
#include "Raportable.h"
#include <fstream>
#include <string>



std::vector<unsigned> CsvGeneratorReader::readthefile(std::string filename)
{
	std::ifstream generatorcsv;
	generatorcsv.open(filename);
	while (generatorcsv.good())
	{
		std::string odds;
		getline(generatorcsv, odds, ',');
		unsigned uns_odds = std::stoul(odds, nullptr, 10);
		odds.push_back(uns_odds);
	}
	generatorcsv.close();
	return odds;
};