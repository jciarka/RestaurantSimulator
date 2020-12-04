#include "MainCourse.h"
#include <sstream>

MainCourse::MainCourse(unsigned preparing_time, unsigned eating_time, std::string name,
    price dish_price, ITrigger* global_trigger, IRaporter* global_raporter)
    : DishBase(preparing_time, eating_time, name, dish_price, global_trigger, global_raporter)
{
}

MainCourse::MainCourse(MainCourse&& main_course) : DishBase(std::move(main_course))
{
}

std::string MainCourse::to_string() const
{
    std::stringstream description;
    description << "main course " << DishBase::get_name() << " " << DishBase::get_id();
    return std::string(description.str());
}

