
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
// Czêœæ statyczna
unsigned StandardClient::id_counter = 0; // Inicjacja pocz¹tkowej wartosci od której nadawane bêdzie id

unsigned StandardClient::generate_unique_id()
{
    return ++id_counter;
}
// ______________________________________________________________________________________________________

StandardClient::StandardClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter)
                               : TriggeredCounter(global_trigger), Raportable(global_raporter), choosing_time(choosing_time),
                                 group(nullptr), menu(nullptr), main_course(nullptr), beveage(nullptr),
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
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": wrong state at initiation";
        throw std::logic_error(error_txt_stream.str());
    }

    state = group->get_state();
    this->group = group;
}

void StandardClient::begin_feast()
{
    // SprawdŸ czy wywo³anie we w³aœciwym momencie
    if (!(state == IClient::client_state::WAITING_FOR_FRIENDS || state == IClient::client_state::READY_TO_BEGIN))
    {
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": begin feast call when client not waiting for friends";
        throw std::logic_error(error_txt_stream.str());
    }

    // raport
    std::ostringstream raport_stream;
    raport_stream <<  "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": Begins feast";
    raport(raport_stream.str());

    // Powiadom grupê o zmianie stanu - nie konieczne ale dla zachowania konwencji
    // grupa bêdzie to ignorowaæ
    state = IClient::client_state::WAITING_FOR_CARD;
    group->on_client_state_changed(this);
}

void StandardClient::take_card(const IMenu* menu)
{
    // SprawdŸ czy wywo³anie we w³aœciwym momencie
    if (state != IClient::client_state::WAITING_FOR_CARD)
    {
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": take card call when client not waiting for card";
        throw std::logic_error(error_txt_stream.str());
    }
    // Zapamiêtaj menu, zainicjuj proces zastanawiania siê nad wyborem
    this->menu = menu; // pointing global menu
    set_counter(choosing_time);
    start();

    // Powiadom grupê o zmianie stanu
    state = IClient::client_state::CHOOSING_DISHES;
    group->on_client_state_changed(this);

    // raport
    std::ostringstream raport_stream;
    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": Took menu and begin to choose dishes";
    raport(raport_stream.str());
}

void StandardClient::choose_dishes()
{
    if (menu == nullptr)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": choose dishes call in invalid state";
        throw std::logic_error(error_txt_stream.str());
    }

    // Prepare to raport
    std::ostringstream raport_stream;

    // Choose main course
    srand(time(nullptr));
    unsigned dish_count = menu->get_main_course_size();
    unsigned choosen = rand() % dish_count;
    main_course = menu->get_main_course(choosen);
    main_course->set_client(this);

    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": choosed " << main_course->to_string() << std::endl;
   
    // Choose beverage
    dish_count = menu->get_beverage_size();
    choosen = rand() % dish_count;
    beveage = menu->get_beverage(choosen);
    beveage->set_client(this);
    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": choosed " << beveage->to_string();

    raport(raport_stream.str());
}

// Triggered
void StandardClient::OnCounted()
{
    std::stringstream raport_stream;
    std::stringstream error_txt_stream;
    switch (state)
    {
    case IClient::client_state::CHOOSING_DISHES:
        // Choose dishes
        choose_dishes();

        // Raportuj
        raport_stream << "Table: " << group->get_table()->get_id() <<
                         " Group: " << group->get_id() <<
                         " Client " << id << ": is ready to order";
        raport(raport_stream.str());

        // Powiadom grupê o zmianie stanu
        state = IClient::client_state::READY_TO_ORDER;
        group->on_client_state_changed(this);
        break;

    default:
        // Jeœli nie rzuæ wyj¹tek
        error_txt_stream << "Client " << id << ": on_counted call in invalid state";
        throw std::logic_error(error_txt_stream.str());
        break;
    }
}

std::vector<IOrder*> StandardClient::create_orders()
{
    std::vector<IOrder*> orders;
    orders.push_back(new Order(beveage, this));
    orders.push_back(new Order(main_course, this));
    return orders;
}


std::vector<IOrder*> StandardClient::give_order()
{
    // SprawdŸ czy wywo³anie we w³aœciwym momencie
    if (state != IClient::client_state::READY_TO_ORDER)
    {
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": give_order call when client not ready to order";
        throw std::logic_error(error_txt_stream.str());
    }

    std::vector<IOrder*> orders = create_orders();

    // Raportuj
    std::stringstream raport_stream;
    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": has ordered";
    raport(raport_stream.str());

    // Powiadom grupê o zmianie stanu
    state = IClient::client_state::WAITING_FOR_DISHES;
    group->on_client_state_changed(this);

    return orders;
}

void StandardClient::pick_up_order(IOrder* order)
{
    if (state == IClient::client_state::WAITING_FOR_DISHES || state == IClient::client_state::EATING)
    {
        // Resolve dish and delete order
        IDish* dish = order->get_dish();
        delete order; 

        if (dish != beveage && dish != main_course)
        {
            // Jeœli nie rzuæ wyj¹tek
            std::stringstream error_txt_stream;
            error_txt_stream << "Client " << id << ": recieved someone's else dish";
            throw std::logic_error(error_txt_stream.str());
        }
        // Main course and beverage are consumed at the same time
        dish->begin_eat();

        // Raportuj
        std::stringstream raport_stream;
        raport_stream << "Table: " << group->get_table()->get_id() <<
                         " Group: " << group->get_id() <<
                         " Client " << id << 
                         ": starts consuming " << dish->to_string();
        raport(raport_stream.str());

        if (state == IClient::client_state::WAITING_FOR_DISHES)
        {
            // Powiadom grupê o zmianie stanu
            state = IClient::client_state::EATING;
            group->on_client_state_changed(this);
        }
    }
    else
    {
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": pick_up_order call when client not waiting for order and not eating";
        throw std::logic_error(error_txt_stream.str());
    }
}

void StandardClient::on_dish_state_change(IDish* dish)
{
    if (dish != beveage && dish != main_course)
    {
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": recieved notify that someone's else dish was eaten";
        throw std::logic_error(error_txt_stream.str());
    }

    if (dish->get_state() == IDish::dish_state::EATEN && state != IClient::client_state::EATING)
    {
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Client " << id << ": client wasn't eating, but dish got eaten";
        throw std::logic_error(error_txt_stream.str());
    }

    // Raportuj
    std::stringstream raport_stream;
    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": consumed " << dish->to_string();
    raport(raport_stream.str());

    if (beveage->get_state() == IDish::dish_state::EATEN && main_course->get_state() == IDish::dish_state::EATEN)
    {
        // Powiadom grupê o zmianie stanu
        state = IClient::client_state::FINISHED_EATING;
        group->on_client_state_changed(this);
    }
}

price StandardClient::count_total()
{
    return beveage->get_price() + main_course->get_price();
}

void StandardClient::pay()
{
    price total = count_total();

    // Raportuj
    std::stringstream raport_stream;
    raport_stream << "Table: " << group->get_table()->get_id() <<
                     " Group: " << group->get_id() <<
                     " Client " << id << ": paying " << total;
    raport(raport_stream.str());

    // Powiadom grupê o zmianie stanu
    state = IClient::client_state::LEAVING;
    group->on_client_state_changed(this);
}

StandardClient::~StandardClient() // Zniszcz dania,
{  
    delete main_course;
    main_course = nullptr;
    delete beveage;
    beveage = nullptr;
}

// ______________________________________________________________________________________________________
// Czêœc obiektu

