#include "IClient.h"

std::ostream& operator<<(std::ostream& os, const IClient& client)
{
    return os << "Client " << client.get_id();
}
