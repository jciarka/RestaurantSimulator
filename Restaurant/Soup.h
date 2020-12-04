#pragma once
#include "DishBase.h"


class Soup : public DishBase
{
public:
    Soup(unsigned preparing_time, unsigned eating_time, std::string name,
        price dish_price, ITrigger* global_trigger, IRaporter* global_raporter);
    
    Soup(Soup&& soup); // Moving constructor
    virtual std::string to_string() const override;
    virtual ~Soup() {};
};
