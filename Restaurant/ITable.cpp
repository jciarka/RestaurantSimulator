#include "ITable.h"

std::ostream& operator<<(std::ostream& os, const ITable& table)
{
	return os << "Table " << table.get_id();
}