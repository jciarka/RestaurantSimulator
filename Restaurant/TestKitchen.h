#pragma once

#include "IKitchen.h"
#include <iostream>

class TestKitchen : public IKitchen
{

public:
    virtual void take_order(IOrder* order) override { };
    virtual IOrder* deliver_preapared() override { return nullptr; };
    virtual void on_dish_state_change(IDish* dish) override 
    {
        std::cout << "Test kitchen - dish state changed "<< std::endl;
    };

    virtual ~TestKitchen() override {};
};

