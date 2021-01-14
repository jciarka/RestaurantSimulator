#include "HungryDessertLovingClient.h"

#include <stdexcept>
#include <sstream>
#include <stdlib.h>
#include <chrono>
#include <random>
#include "Order.h"
#include "MainCourse.h"
#include "Beverage.h"
#include "Price.h"
#include "Table.h"


HungryDessertLovingClient::HungryDessertLovingClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter)
                                                   : StandardClient(choosing_time, global_trigger, global_raporter)
{
}


void HungryDessertLovingClient::choose_dishes()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    unsigned soup_count = menu->get_soup_size();
    unsigned choosen = generator() % soup_count;

    soup = new Soup(menu->get_soup(choosen));
    soup->set_client(this);

    // Choose main course and beverage
    StandardClient::choose_dishes();

    // Rand number of soup
    srand(time(nullptr));
    unsigned dessert_count = menu->get_dessert_size();
    choosen = generator() % dessert_count;

    dessert = new Dessert(menu->get_dessert(choosen));
    dessert->set_client(this);

    // Raport
    std::ostringstream raport_stream;
    raport_stream << *this << " chose " << *dessert << std::endl;
    raport_stream << *this << " chose " << *soup;
    raport(raport_stream.str());
}