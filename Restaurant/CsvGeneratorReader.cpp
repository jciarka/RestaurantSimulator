#include "CsvGeneratorReader.h"
#include "Triggered.h"
#include "Raportable.h"
#include <fstream>
#include <string>
#include <sstream>


std::vector<unsigned> CsvGeneratorReader::readthefile(std::string filename)
{
	std::ifstream generatorcsv;
	generatorcsv.open(filename);
	if (!(generatorcsv.is_open()))
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "File: " << filename << " could not be opened";
		throw std::invalid_argument(error_txt_stream.str());
	}
	std::vector<unsigned> return_vector;
	while (generatorcsv.good())
	{
		std::string odds;
		getline(generatorcsv, odds, ',');
		unsigned uns_odds = std::stoul(odds, nullptr, 10);
		return_vector.push_back(uns_odds);
	}
	generatorcsv.close();
	if (!(return_vector.size() == 10))
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "File: " << filename << " contains wrong amount of arguments, the number of arguments needs to be 10.";
		throw std::logic_error(error_txt_stream.str());
	}
	return return_vector;
};