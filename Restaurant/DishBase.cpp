#include <sstream>
#include "DishBase.h"
#include "IClient.h"
#include "IKitchen.h"


// ______________________________________________________________________________________________________
// Czêœæ statyczna
unsigned DishBase::id_counter = 0; // Inicjacja pocz¹tkowej wartosci od której nadawane bêdzie id

unsigned DishBase::generate_unique_id()
{
    return ++id_counter;
}
// ______________________________________________________________________________________________________


DishBase::DishBase(unsigned preparing_time, unsigned eating_time, std::string name, price dish_price,
                   ITrigger& global_trigger, IRaporter& global_raporter)
    : TriggeredCounter(global_trigger), Raportable(global_raporter),
      name(name), preparing_time(preparing_time), eating_time(eating_time), state(IDish::dish_state::CHOOSEN), dish_price(dish_price), 
      client(nullptr), kitchen(nullptr), id(generate_unique_id())
{
}

void DishBase::set_client(IClient* client)
{
    if (client == nullptr)
    {
        // Rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << ": client is not set";
        throw std::logic_error(error_txt_stream.str());
    }

    this->client = client;
}

void DishBase::set_kitchen(IKitchen* kitchen)
{
    if (kitchen == nullptr)
    {
        // Rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << ": kitchen must not be null";
        throw std::logic_error(error_txt_stream.str());
    }

    this->kitchen = kitchen;
}


void DishBase::begin_preparing()
{
    // SprawdŸ czy wywo³anie we w³aœciwym momencie
    if (state != IDish::dish_state::CHOOSEN)
    {
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << ": begin_preparing call when dish is not choosen";
        throw std::logic_error(error_txt_stream.str());
    }

    if (kitchen == nullptr)
    {
        // Kuchnia musi byæ w tym momencie ju¿ okreœlona
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << ": begin_preparing call when kitchen is not set";
        throw std::logic_error(error_txt_stream.str());
    }

    /*
    // raport
    std::ostringstream raport_steram;
    raport_steram << this->to_string() << ", id:" << id 
                  << " for Client " << this->client->get_id() 
                  << " is being prepared";
    raport(raport_steram.str());
    */
    // Zainicjuj proces przygotowania
    set_counter(preparing_time);
    start();

    // Powiadom kuchniê o zmianie stanu - nie jest konieczny, bêdzie ignorowany 
    state = IDish::dish_state::PREPARATION;
    //kitchen->on_dish_state_change(this);
}

void DishBase::OnCounted()
{
    std::stringstream raport_stream;
    std::stringstream error_txt_stream;
    switch (state)  
    {
    case IDish::dish_state::PREPARATION:
        /*
        // Raportuj
        raport_stream << this->to_string() << ", id:" << id
                      << " for Client " << this->client->get_id()
                      << " is ready for delivery";
        raport(raport_stream.str());
        */
        // Powiadom kuchniê o zmianie stanu - nie jest konieczny, bêdzie ignorowany 
        state = IDish::dish_state::PREPARED;
        kitchen->on_dish_state_change(this);
        break;

    case IDish::dish_state::CONSUMPTION:
        /**/
        // Raportuj
        // raport_stream << "Dish " << id << ": is eaten" << std::endl;
        // raport(raport_stream.str());

        // Powiadom kuchniê o zmianie stanu - nie jest konieczny, bêdzie ignorowany 
        state = IDish::dish_state::EATEN;
        client->on_dish_state_change(this);
        break;

    default:
        error_txt_stream << "Dish " << id << ": on_counted call when dish is not beeing prepared or eaten" << std::endl;
        throw std::logic_error(error_txt_stream.str());
        break;
    }
}

void DishBase::begin_eat()
{
    // SprawdŸ czy wywo³anie we w³aœciwym momencie
    if (state != IDish::dish_state::PREPARED)
    {
        // Jeœli nie rzuæ wyj¹tek
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << ": begin_eat call when dish is not prepared";
        throw std::logic_error(error_txt_stream.str());
    }

    if ( client == nullptr)
    {
        // Kuchnia musi byæ w tym momencie ju¿ okreœlona
        std::stringstream error_txt_stream;
        error_txt_stream << "Dish " << id << ": begin_eat call when klient is not set";
        throw std::logic_error(error_txt_stream.str());
    }
    /*
    // raport
    //std::ostringstream raport_steram;
    //raport_steram << "Dish " << id << ": is begined to eat" << std::endl;
    //raport(raport_steram.str());
    */
    // Zainicjuj proces przygotowania
    set_counter(eating_time);
    start();

    state = IDish::dish_state::CONSUMPTION;
}

price DishBase::get_price()
{
    return dish_price;
}


