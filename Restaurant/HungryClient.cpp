
#include <stdexcept>
#include <sstream>
#include <stdlib.h>
#include <time.h>
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
    srand(time(nullptr));
    unsigned soup_count = menu->get_soup_size();
    unsigned choosen = rand() % soup_count;


    soup = new Soup(menu->get_soup(choosen));
    soup->set_client(this);

    // Raport
    raport_stream << *this << " choosed " << *soup;
    raport(raport_stream.str());

    // Choose main course and beverage
    StandardClient::choose_dishes();
}
