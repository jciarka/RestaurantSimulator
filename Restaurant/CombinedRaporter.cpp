#include "CombinedRaporter.h"
#include <fstream>

void CombinedRaporter::raport(std::string message)
{
	file.raport(message);
	terminal.raport(message);
}