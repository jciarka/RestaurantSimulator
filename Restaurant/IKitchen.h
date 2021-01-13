#pragma once

#include "fwd_include.h"
#include "IDish.h"

class IKitchen
{
public:
    virtual void take_order(IDish* order) = 0;
    virtual IDish* deliver_preapared() = 0;
    virtual void  on_dish_state_change(IDish* dish) = 0;

    virtual ~IKitchen() = 0 {};
};

