#include "Order.h"

// ______________________________________________________________________________________________________
// Static part
unsigned Order::id_counter = 0;

unsigned Order::generate_unique_id()
{
    return ++id_counter;
}
// ______________________________________________________________________________________________________
