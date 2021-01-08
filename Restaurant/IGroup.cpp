#include "IGroup.h"
#include "ITable.h"

std::ostream& operator<<(std::ostream& os, const IGroup& group)
{
	return os << "Group " << group.get_id() << " at " << *(group.get_table());
}