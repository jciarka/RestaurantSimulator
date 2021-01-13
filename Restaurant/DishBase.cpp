#include <sstream>
#include <stdexcept>
#include "DishBase.h"
#include "IClient.h"
#include "IKitchen.h"


// ______________________________________________________________________________________________________
// Static part
unsigned DishBase::id_counter = 0; // Intitial value at program start

unsigned DishBase::generate_unique_id()
{
    return ++id_counter;
}
// ______________________________________________________________________________________________________


DishBase::DishBase(unsigned preparing_time, unsigned eating_time, std::string name, price dish_price,
                   ITrigger* global_trigger, IRaporter* global_raporter)
    : TriggeredCounter(global_trigger), Raportable(global_raporter),
      name(name), preparing_time(preparing_time), eating_time(eating_time), state(IDish::dish_state::CHOOSEN), dish_price(dish_price), 
      client(nullptr), kitchen(nullptr), id(generate_unique_id())
{
}

DishBase::DishBase(DishBase&& dish) noexcept : TriggeredCounter(dish.global_trigger_ptr), Raportable(dish.global_raporter_ptr),
name(dish.name), preparing_time(dish.preparing_time), eating_time(dish.eating_time), state(IDish::dish_state::CHOOSEN), dish_price(dish.dish_price),
client(nullptr), kitchen(nullptr), id(dish.id)
{
    dish.id = std::numeric_limits<unsigned>::max();
    dish.name = "Invalid";
    dish.preparing_time = 0;
    dish.eating_time = 0;
    dish.dish_price = 0;
    dish.state = IDish::dish_state::EATEN;
}

void DishBase::set_client(IClient* client)
{
    if (client == nullptr)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << " client is not set";
        throw std::logic_error(error_txt_stream.str());
    }

    this->client = client;
}

void DishBase::set_kitchen(IKitchen* kitchen)
{
    if (kitchen == nullptr)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << " kitchen must not be null";
        throw std::logic_error(error_txt_stream.str());
    }

    this->kitchen = kitchen;
}

/// <summary>
/// Initiates preparing proces using dishe's counter
/// </summary>
void DishBase::begin_preparing()
{
    // Check if called at a wright time
    if (state != IDish::dish_state::CHOOSEN)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << " begin_preparing call when dish is not choosen";
        throw std::logic_error(error_txt_stream.str());
    }

    if (kitchen == nullptr)
    {
        // Kitchen must be set at this moment
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << " begin_preparing call when kitchen is not set";
        throw std::logic_error(error_txt_stream.str());
    }

    // Initiate preparation proces
    set_counter(preparing_time);
    start();

    // Change state
    state = IDish::dish_state::PREPARATION;

    // Raport
    std::ostringstream raport_stream;
    raport_stream << "Kitchen beginning preparation of " << *this << " for " << *client;
    raport(raport_stream.str());
}

/// <summary>
/// Counter logic - preparation and eating
/// </summary>
void DishBase::OnCounted()
{
    std::stringstream raport_stream;
    std::stringstream error_txt_stream;
    switch (state)  
    {
    case IDish::dish_state::PREPARATION:

        // Notify kitchen about state change
        state = IDish::dish_state::PREPARED;
        kitchen->on_dish_state_change(this);

        raport_stream << "Kitchen " << *this << " for " << *client << " prepared";
        raport(raport_stream.str());
        break;

    case IDish::dish_state::CONSUMPTION:
        // Notify kitchen about state change 
        state = IDish::dish_state::EATEN;
        client->on_dish_state_change(this);
        break;

    default:
        error_txt_stream << "Dish " << id << " on_counted call when dish is not beeing prepared or eaten" << std::endl;
        throw std::logic_error(error_txt_stream.str());
        break;
    }
}


/// <summary>
/// Delivers dish for waiter
/// </summary>
void DishBase::deliver()
{
    if (state != IDish::dish_state::PREPARED)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << " deliver call when dish is not prepared";
        throw std::logic_error(error_txt_stream.str());
    }

    state = IDish::dish_state::DELIVERED;
    client->pick_up_order(this);
}

/// <summary>
/// Initiates eating proces using dishe's counter
/// </summary>
void DishBase::begin_eat()
{
    // Check if called at wright time
    if (state != IDish::dish_state::DELIVERED)
    {
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << " begin_eat call when dish is not delivered";
        throw std::logic_error(error_txt_stream.str());
    }

    if ( client == nullptr)
    {
        // Kitchen must be set at tkis moment
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << " begin_eat call when klient is not set";
        throw std::logic_error(error_txt_stream.str());
    }
    
    // Initiate eating proces
    set_counter(eating_time);
    start();

    state = IDish::dish_state::CONSUMPTION;
}

price DishBase::get_price()
{
    return dish_price;
}


