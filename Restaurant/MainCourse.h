#pragma once
#include "DishBase.h"

class MainCourse : public DishBase
{
public:
    MainCourse(unsigned preparing_time, unsigned eating_time, std::string name, IDish::dish_state state,
        price dish_price, ITrigger & global_trigger, IRaporter & global_raporter);
    virtual std::string to_string() const override;
    virtual ~MainCourse() {};
};
