#include "Soup.h"
#include <sstream>

Soup::Soup(unsigned preparing_time, unsigned eating_time, std::string name,
           price dish_price, ITrigger* global_trigger, IRaporter* global_raporter)
    : DishBase(preparing_time, eating_time, name, dish_price, global_trigger, global_raporter)
{
}

Soup::Soup(Soup&& soup) : DishBase(std::move(soup))
{
}

std::string Soup::to_string() const
{
    std::stringstream description;
    description << "soup " << DishBase::get_name() << " " << DishBase::get_id();
    return std::string(description.str());
}
