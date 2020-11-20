#pragma once
#include "IOrder.h"

class IKitchen
{
    // vector Iorder w prztgotowaniu -> begin preparing()
    // kolejka IOreder do wydania

public:
    virtual IOrder* take_order() = 0;
    virtual IOrder* get_preapared() = 0;
    virtual IDish*  on_dish_state_change() = 0;

    virtual ~IKitchen() = 0 {};
};

