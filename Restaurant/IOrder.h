#pragma once
#include <iostream>
#include <vector>
#include "IDish.h"
#include "IMenu.h"

class IOrder
{
public:
    // Aviable states for client
    enum class order_state {
        ORDERED,
        PREPARATION,
        PREPARED
    };

    // typedef function type for raporting
    typedef void (*raport)(std::vector<std::ostream*>);

    // typedef state changed functions 
    typedef void (*order_state_changed_event_handler)(IOrder* sender, order_state new_state);

    //void add_order_state_changed_event_handler(order_state_changed_event_handler* event_handler);
    //void remove_order_state_changed_event_handler(order_state_changed_event_handler* event_handler);

    // interface methods
    virtual unsigned get_id() const = 0;
    virtual order_state get_state() const = 0;

    // Interface for Group
    virtual std::vector<IDish*>::iterator get_dishes() = 0;

    // Interface for kitchen
    virtual void begin_preparing() = 0;

    virtual ~IOrder() = 0;
};