#pragma once
#include <iostream>
#include <vector>

class IDish
{
public:
    enum class dish_state {
        ORDERED,
        PREPARATION,
        PREPARED,
        CONSUMPTION,
        EATEN,
    };

    // typedef function type for raporting
    typedef void (*raport)(std::vector<std::ostream*>);

    // typedef state changed functions 
    typedef void (*dish_state_changed_event_handler)(IClient* sender, dish_state new_state);

    //void add_client_state_changed_event_handler(dish_state_changed_event_handler* event_handler);
    //void remove_client_state_changed_event_handler(dish_state_changed_event_handler* event_handler);

    virtual dish_state get_state() const = 0;
    virtual void begin_preparing() = 0;

    // Interface for IOrder
    virtual void begin_preparing() = 0;

    // interface for IClient
    virtual void begin_eat() = 0;

    virtual void execute_iteration() = 0;

    virtual ~IDish() = 0;

};
