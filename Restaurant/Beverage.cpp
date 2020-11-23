#include <sstream>
#include "Beverage.h"

Beverage::Beverage(unsigned preparing_time, unsigned eating_time, std::string name, IDish::dish_state state, 
                   price dish_price, ITrigger& global_trigger, IRaporter& global_raporter)
    : DishBase(preparing_time, eating_time, name, state, dish_price, global_trigger, global_raporter)
{
}

std::string Beverage::to_string() const
{
    std::stringstream description;
    description << "beverage, type: " << DishBase::get_name() << " id: " << DishBase::get_id();
    return std::string();
}