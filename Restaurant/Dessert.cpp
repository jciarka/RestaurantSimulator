#include "Dessert.h"
#include <sstream>

Dessert::Dessert(unsigned preparing_time, unsigned eating_time, std::string name,
                 price dish_price, ITrigger* global_trigger, IRaporter* global_raporter)
        : DishBase(preparing_time, eating_time, name, dish_price, global_trigger, global_raporter) 
{
}

Dessert::Dessert(Dessert&& dessert) : DishBase(std::move(dessert))
{
}

std::string Dessert::to_string() const
{
    std::stringstream description;
    description << "dessert " << DishBase::get_name() << " " << DishBase::get_id();
    return std::string(description.str());
}
