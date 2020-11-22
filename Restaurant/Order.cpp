#include "Order.h"

// ______________________________________________________________________________________________________
// Czêœæ statyczna
unsigned Order::id_counter = 0; // Inicjacja pocz¹tkowej wartosci od której nadawane bêdzie id

unsigned Order::generate_unique_id()
{
    return ++id_counter;
}
// ______________________________________________________________________________________________________
