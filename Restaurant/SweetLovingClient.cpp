
#include "SweetLovingClient.h"

#include <stdexcept>
//#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "Order.h"
#include "MainCourse.h"
#include "Beverage.h"
#include "Price.h"

/*

SweetLovingClient::SweetLovingClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter)
                                   : StandardClient(choosing_time, global_trigger, global_raporter)
{
}


/*
void SweetLovingClient::choose_dishes()
{
    // Choose soup
    std::ostringstream raport_stream;

    // Choose main course and beverage
    StandardClient::choose_dishes();


    // Rand number of soup
    srand(time(nullptr));
    unsigned dessert_count = menu->get_dessert_size();
    unsigned choosen = rand() % dessert_count;

    dessert = new Dessert(menu->get_dessert(choosen));
    dessert->set_client(this);

    // Raport
    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": choosed " << dessert->to_string() << std::endl;
    raport(raport_stream.str());
}


/*
std::vector<IDish*> SweetLovingClient::create_orders()
{
    std::vector<IDish*> order = StandardClient::create_orders();
    order.push_back(dessert);
    return order;
}


void SweetLovingClient::pick_up_order(IDish* dish)
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
    if (dish == main_course || dish == beveage)
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
    else if (dish == dessert)
    {
        // Begin eating main_course only when soup is finished
        if (main_course->get_state() == IDish::dish_state::EATEN)
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

void SweetLovingClient::on_dish_state_change(IDish* dish)
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
    if (dish == main_course && dessert->get_state() == IDish::dish_state::DELIVERED)
    {
        main_course->begin_eat();
    }

    // Standard client condition for fisnish eating
    if (beveage->get_state() == IDish::dish_state::EATEN && dessert->get_state() == IDish::dish_state::EATEN)
    {
        // Notify the group about the change of state
        state = IClient::client_state::FINISHED_EATING;
        group->on_client_state_changed(this);
    }
}

price SweetLovingClient::count_total()
{
    return StandardClient::count_total() + dessert->get_price();
}

SweetLovingClient::~SweetLovingClient()
{
    if (dessert != nullptr)
    {
        delete dessert;
        dessert = nullptr;
    }
}

*/