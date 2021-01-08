#include "IDish.h"

std::ostream& operator<<(std::ostream& os, const IDish& dish)
{
	return os << dish.to_string();
} 