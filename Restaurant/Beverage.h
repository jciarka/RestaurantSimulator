#pragma once
#include "IDish.h"

class Beverage : public IDish
{
    /*
    TO DO:

    // pami�taj wska�nik IClient -> on_dish_state_change()
    // IKitchen -> on_dish_state_change()
    */
public:

    virtual ~Beverage() override {};
};
