#pragma once
#include "IOrder.h"

class IKitchen
{
    // vector Iorder w prztgotowaniu -> begin preparing()
    // kolejka IOreder do wydania

public:
    virtual void take_order(IOrder* order) = 0;
    virtual IOrder* deliver_preapared() = 0;
    virtual void  on_dish_state_change(IDish* dish) = 0;

    virtual ~IKitchen() = 0 {};
};

