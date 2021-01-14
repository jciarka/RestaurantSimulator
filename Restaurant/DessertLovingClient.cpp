#include "DessertLovingClient.h"

#include <stdexcept>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "Order.h"
#include "MainCourse.h"
#include "Beverage.h"
#include "Price.h"
#include "Table.h"


DessertLovingClient::DessertLovingClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter)
                                   : StandardClient(choosing_time, global_trigger, global_raporter)
{
}


void DessertLovingClient::choose_dishes()
{
    // Choose main course and beverage
    StandardClient::choose_dishes();

    // Rand number of soup
    srand(time(nullptr));
    unsigned dessert_count = menu->get_dessert_size();
    unsigned choosen = rand() % dessert_count;

    dessert = new Dessert(menu->get_dessert(choosen));
    dessert->set_client(this);

    // Raport
    std::ostringstream raport_stream;
    raport_stream << *this << " chose " << *dessert;
    raport(raport_stream.str());
}