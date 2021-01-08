
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


/*

HungryClient::HungryClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter)
	                       : soup(nullptr), StandardClient(choosing_time, global_trigger, global_raporter)
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
    raport_stream << "Table: " << group->get_table()->get_id() <<
        " Group: " << group->get_id() <<
        " Client " << id << ": choosed " << soup->to_string() << std::endl;

	// Choose main course and beverage
	StandardClient::choose_dishes();
}


std::vector<IDish*> HungryClient::create_orders()
{
	 std::vector<IDish*> order = StandardClient::create_orders();
	 order.push_back(soup);
	 return order;
}


void HungryClient::pick_up_order(IDish* dish)
{
    if (!(state == IClient::client_state::WAITING_FOR_DISHES || state == IClient::client_state::EATING))
    {
        // In other states throw exceptions
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": pick_up_order call when client not waiting for order and not eating";
        throw std::logic_error(error_txt_stream.str());
    
    }

    std::stringstream raport_stream;
    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id <<
                     ": starts consuming " << dish->to_string();

    // Resolve dish
    if (dish == soup || dish == beveage)
    {
        // Begin eating soup immediately
        dish->begin_eat();
        raport(raport_stream.str());

        // if this is first dish 
        if (state == IClient::client_state::WAITING_FOR_DISHES)
        {
            state = IClient::client_state::EATING;
            group->on_client_state_changed(this);
        }
        return;
    }
    else if (dish == main_course)
    {
        // Begin eating main_course only when soup is finished
        if (soup->get_state() == IDish::dish_state::EATEN)
        {
            dish->begin_eat();
            raport(raport_stream.str());
        }
        // else wait untill soup is eaten
        return;
    }

    // Other option is not allowed - throw exception
    std::stringstream error_txt_stream;
    error_txt_stream << "Client " << id << ": recieved someone's else dish";
    throw std::logic_error(error_txt_stream.str());

}

void HungryClient::on_dish_state_change(IDish* dish)
{
    if (dish->get_state() == IDish::dish_state::EATEN && state != IClient::client_state::EATING)
    {
        // If client wasn't eating, but dish got eaten throw exception
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": client wasn't eating, but dish got eaten";
        throw std::logic_error(error_txt_stream.str());
    }

    // Raport
    std::stringstream raport_stream;
    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": consumed " << dish->to_string();
    raport(raport_stream.str());

    // If main course delivered and finished eating soup
    // now can start eating main_course
    if (dish == soup && main_course->get_state() == IDish::dish_state::DELIVERED)
    {
        main_course->begin_eat();
    }

    // Standard client condition for fisnish eating
    if (beveage->get_state() == IDish::dish_state::EATEN && main_course->get_state() == IDish::dish_state::EATEN)
    {
        // Notify the group about the change of state
        state = IClient::client_state::FINISHED_EATING;
        group->on_client_state_changed(this);
    }
}

price HungryClient::count_total()
{
	return StandardClient::count_total() + soup->get_price();
}

HungryClient::~HungryClient()
{
	if (soup != nullptr)
	{
		delete soup;
		soup = nullptr;
	}
}

*/