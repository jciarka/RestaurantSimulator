
#include <stdexcept>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "StandardClient.h"
#include "IGroup.h"
#include "ITable.h"
#include "Order.h"
#include "MainCourse.h"
#include "Beverage.h"
#include "Price.h"



// ______________________________________________________________________________________________________
// STATIC PART
unsigned StandardClient::id_counter = 0;

unsigned StandardClient::generate_unique_id()
{
    return ++id_counter;
}
// ______________________________________________________________________________________________________

StandardClient::StandardClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter)
                               : TriggeredCounter(global_trigger), Raportable(global_raporter), choosing_time(choosing_time),
                                 group(nullptr), menu(nullptr), 
                                 beveage(nullptr), soup(nullptr), main_course(nullptr),  dessert(nullptr),
                                 id(generate_unique_id()), state(client_state::INITIATION)
{
}

void StandardClient::set_group(IGroup* group)
{
    if (group == nullptr)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": group can't be nullptr at clients creation";
        throw std::logic_error(error_txt_stream.str());
    }

    if (!(group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS || group->get_state() == IClient::client_state::READY_TO_BEGIN))
    {
        // Thow excetion if not state at initiation
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": wrong state at initiation";
        throw std::logic_error(error_txt_stream.str());
    }

    state = group->get_state();
    this->group = group;
}

void StandardClient::begin_feast()
{
    // Check if calling at the right time
    if (!(state == IClient::client_state::WAITING_FOR_FRIENDS || state == IClient::client_state::READY_TO_BEGIN))
    {
        // Thow excetion if not
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": begin feast call when client not waiting for friends";
        throw std::logic_error(error_txt_stream.str());
    }

    // Raport
    std::ostringstream raport_stream;
    raport_stream <<  *this << " Begins feast";
    raport(raport_stream.str());

    // Notify the group about the change of state
    state = IClient::client_state::WAITING_FOR_CARD;
    group->on_client_state_changed(this);
}

void StandardClient::take_card(const IMenu* menu)
{
    // Check if calling at the right time
    if (state != IClient::client_state::WAITING_FOR_CARD)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << " take card call when client not waiting for card";
        throw std::logic_error(error_txt_stream.str());
    }
    // Remember the menu, initiate the process of considering the choice
    this->menu = menu; // pointing global menu
    set_counter(choosing_time);
    start();

    // Notify the group about the change of state
    state = IClient::client_state::CHOOSING_DISHES;
    group->on_client_state_changed(this);

    // Raport
    std::ostringstream raport_stream;
    raport_stream << *this << " Took menu and begun to choose dishes";
    raport(raport_stream.str());
}

/// <summary>
/// Choose and create dishes from menu
/// Set the dishes pointers poles
/// </summary>
void StandardClient::choose_dishes()
{
    if (menu == nullptr)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << " choose dishes call in invalid state";
        throw std::logic_error(error_txt_stream.str());
    }

    // Prepare to raport
    std::ostringstream raport_stream;

    // Choose main course
    srand(time(nullptr));
    unsigned dish_count = menu->get_main_course_size();
    unsigned choosen = rand() % dish_count;
    main_course =new MainCourse(menu->get_main_course(choosen));
    main_course->set_client(this);

    raport_stream << *this << " chose " << *main_course << std::endl;
   
    // Choose beverage
    dish_count = menu->get_beverage_size();
    choosen = rand() % dish_count;
    beveage = new Beverage(menu->get_beverage(choosen));
    beveage->set_client(this);
    raport_stream << *this << " chose " << *beveage;

    raport(raport_stream.str());
}

// Triggered
/// <summary>
/// Logic of time dependent event - choosing dishes
/// </summary>
void StandardClient::OnCounted()
{
    std::stringstream raport_stream;
    std::stringstream error_txt_stream;
    switch (state)
    {
    case IClient::client_state::CHOOSING_DISHES:
        // Choose dishes
        choose_dishes();

        // Raport
        raport_stream << *this << " is ready to order";
        raport(raport_stream.str());

        // Notify the group about the change of state
        state = IClient::client_state::READY_TO_ORDER;
        group->on_client_state_changed(this);
        break;

    default:
        // In other states throw exception
        error_txt_stream << "Client " << id << " on_counted call in invalid state";
        throw std::logic_error(error_txt_stream.str());
        break;
    }
}


/// <summary>
/// Form order from dishes
/// </summary>
std::vector<IDish*> StandardClient::create_orders()
{
    std::vector<IDish*> orders;
    if (beveage != nullptr)
    {
        orders.push_back(beveage);
    }

    if (soup != nullptr)
    {
        orders.push_back(soup);
    }
    
    if (main_course != nullptr)
    {
        orders.push_back(main_course);
    }

    if (dessert != nullptr)
    {
        orders.push_back(dessert);
    }
    return orders;
}


std::vector<IDish*> StandardClient::give_order()
{
    // Check if calling at the right time
    if (state != IClient::client_state::READY_TO_ORDER)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << " give_order call when client not ready to order";
        throw std::logic_error(error_txt_stream.str());
    }

    std::vector<IDish*> orders = create_orders();

    // Raport
    std::stringstream raport_stream;
    raport_stream << *this << " has ordered";
    raport(raport_stream.str());

    // Notify the group about the change of state
    state = IClient::client_state::WAITING_FOR_DISHES;
    group->on_client_state_changed(this);

    return orders;
}

bool StandardClient::null_or_eaten(IDish* dish)
{
    if (dish == nullptr)
    {
        return true;
    }
    else if (dish->get_state() == IDish::dish_state::EATEN)
    {
        return true;
    }
    return false;
}


void StandardClient::pick_up_order(IDish* dish)
{
    if (state == IClient::client_state::WAITING_FOR_DISHES || state == IClient::client_state::EATING)
    {

        if (!(state == IClient::client_state::WAITING_FOR_DISHES || state == IClient::client_state::EATING))
        {
            // In other states throw exceptions
            std::stringstream error_txt_stream;
            error_txt_stream << "Client " << id << " pick_up_order call when client not waiting for order and not eating";
            throw std::logic_error(error_txt_stream.str());

        }

        if (state == IClient::client_state::WAITING_FOR_DISHES)
        {
            // Notify the group about the change of state
            state = IClient::client_state::EATING;
            group->on_client_state_changed(this);
        }


        std::stringstream raport_stream;
        raport_stream << *this << " starts consuming " << *dish;


        // Resolve dish
        if (dish == beveage)
        {
            // Begin eating soup immediately
            dish->begin_eat();
            raport(raport_stream.str());
            return;
        }
        else if (dish == soup)
        {
            // Begin eating soup immediately
            dish->begin_eat();
            raport(raport_stream.str());
            return;
        }
        else if (dish == main_course)
        {
            // Begin eating main_course only when soup is finished or wasn't ordered
            if (null_or_eaten(soup))
            {
                dish->begin_eat();
                raport(raport_stream.str());
            }
            // else wait untill soup is eaten
            return;
        }
        else if (dish == dessert)
        {
            // Begin eating main_course only when soup is finished
            if (null_or_eaten(soup) && null_or_eaten(main_course))
            {
                dish->begin_eat();
                raport(raport_stream.str());
            }
            // else wait untill soup is eaten
            return;
        }

        // In other states throw exceptions
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": pick_up_order call when client not waiting for order and not eating";
        throw std::logic_error(error_txt_stream.str());
    }
}

bool StandardClient::not_null_and_delivered(IDish* dish)
{
    if (dish == nullptr)
    {
        return false;
    }
    else if (dish->get_state() != IDish::dish_state::DELIVERED)
    {
        return false;
    }
    return true;
}

std::vector<IDish*> StandardClient::get_dishes_in_order()
{
    std::vector<IDish*> temp;
    if (beveage != nullptr)
        temp.push_back(beveage);
    if (soup != nullptr)
        temp.push_back(soup);
    if (main_course != nullptr)
        temp.push_back(main_course);
    if (dessert != nullptr)
        temp.push_back(dessert);
    return temp;
}

IDish* StandardClient::find_next_if_delivered(IDish* dish)
{
    // Create a vector of dishes in order
    std::vector<IDish*> dishes = get_dishes_in_order();

    // Find next ordered dish
    auto dish_pos = find(dishes.begin(), dishes.end(), dish);
    if ((++dish_pos) != dishes.end())
    {
        // if this dish is delivered - start eating
        if ((*dish_pos)->get_state() == IDish::dish_state::DELIVERED)
        {
            return *dish_pos;
        }
        // else pass
    }
    return nullptr;
}

bool StandardClient::check_all_eaten()
{
    std::vector<IDish*> dishes = get_dishes_in_order();
    for (auto dish : dishes)
    {
        if (dish->get_state() != IDish::dish_state::EATEN)
        {
            return false;
        }
    }
    return true;
}


void StandardClient::on_dish_state_change(IDish* dish)
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
    raport_stream << *this << " consumed " << *dish;
    raport(raport_stream.str());


    // If next dish in order is already delivered - start eating it    
    IDish* next = find_next_if_delivered(dish);
    if (next != nullptr)
    {
        next->begin_eat();

        // Raport
        std::stringstream raport_stream;
        raport_stream << *this << " starts consuming " << *next;
        raport(raport_stream.str());
    }

    // If all dishes are eaten change state
    if (check_all_eaten())
    {
        // Notify the group about the change of state
        state = IClient::client_state::FINISHED_EATING;
        group->on_client_state_changed(this);
    }
}

price StandardClient::count_total()
{
    price price(0);
    std::vector<IDish*> dishes = get_dishes_in_order();
    for (auto dish : dishes)
    {
        price = price + dish->get_price();
    }
    return price;
}

void StandardClient::pay()
{
    price total = count_total();

    // Raport
    std::stringstream raport_stream;
    raport_stream << *this << " paying " << total;
    raport(raport_stream.str());

    // Notify the group about the change of state
    state = IClient::client_state::LEAVING;
    group->on_client_state_changed(this);
}

StandardClient::~StandardClient() // Delete dishes,
{
    if (beveage != nullptr)
    {
        delete beveage;
    }
    if (soup != nullptr)
    {
        delete soup;
    }
    if (main_course != nullptr)
    {
        delete main_course;
    }
    if (dessert != nullptr)
    {
        delete dessert;
    }
}


std::ostream& operator<<(std::ostream& os, const StandardClient& client)
{
    return os << "Client " << client.id << " (" << *(client.group) << ")";
}