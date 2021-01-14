
#include <stdexcept>
#include <sstream>
#include <stdlib.h>
#include <chrono>
#include <random>
#include "HungryClient.h"
#include "StandardClient.h"
#include "IGroup.h"
#include "ITable.h"
#include "Order.h"
#include "MainCourse.h"
#include "Beverage.h"
#include "Price.h"


HungryClient::HungryClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter)
    : StandardClient(choosing_time, global_trigger, global_raporter)
{
}


void HungryClient::choose_dishes()
{
    // Choose soup
    std::ostringstream raport_stream;

    // Rand number of soup
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    unsigned soup_count = menu->get_soup_size();
    unsigned choosen = generator() % soup_count;

    soup = new Soup(menu->get_soup(choosen));
    soup->set_client(this);

    // Raport
    raport_stream << *this << " chose " << *soup;
    raport(raport_stream.str());

    // Choose main course and beverage
    StandardClient::choose_dishes();
}
