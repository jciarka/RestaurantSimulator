#include "Order.h"

// ______________________________________________________________________________________________________
// Cz�� statyczna
unsigned Order::id_counter = 0; // Inicjacja pocz�tkowej wartosci od kt�rej nadawane b�dzie id

unsigned Order::generate_unique_id()
{
    return ++id_counter;
}
// ______________________________________________________________________________________________________
