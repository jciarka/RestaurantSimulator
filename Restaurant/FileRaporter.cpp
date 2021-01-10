#include "FileRaporter.h"
#include <fstream>

void FileRaporter::raport(std::string message)
{
	std::ofstream restaurantraport("restaurantraport.txt", std::ios::out | std::ios::app);
	if (restaurantraport.is_open())
	{
		restaurantraport << message << std::endl;
		restaurantraport.close();
	}
	
}