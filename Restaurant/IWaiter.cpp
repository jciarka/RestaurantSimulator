#include "IWaiter.h"

std::ostream& operator<<(std::ostream& os, const IWaiter& waiter)
{
    return os << "Waiter " << waiter.get_id();
}
