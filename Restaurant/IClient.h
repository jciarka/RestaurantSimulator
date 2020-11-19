#pragma once
#include <iostream>
#include <vector>
#include "IDish.h"
#include "IMenu.h"
#include "IOrder.h"

class IClient
{
public:
    // Aviable states for client
    enum class client_state {
        QUEING,
        WAITING_FOR_CARD,
        CHOOSING_DISHES,
        READY_TO_ORDER,
        WAITING_FOR_DISHES,
        EATING,
        FINISHED_EATING,
        READY_TO_PAY,
    };

    // typedef function type for raporting
    typedef void (*raport)(std::vector<std::ostream*>);

    // typedef state changed functions 
    typedef void (*client_state_changed_event_handler)(IClient* sender, client_state new_state);

    //void add_client_state_changed_event_handler(client_state_changed_event_handler* event_handler);
    //void remove_client_state_changed_event_handler(client_state_changed_event_handler* event_handler);


    virtual unsigned get_id() const = 0;
    virtual client_state get_state() const = 0;

    // Interface for IGroup
    virtual void take_card(const IMenu* menu) = 0;
    virtual std::vector<IDish*> give_order() const = 0; // Creates new Order 
                                            // and new Dishes (MUST REMEMBER TO delete the after eating)
    virtual void pick_up_order(std::vector<IDish*> give_order()) = 0; //Deletes fullfilled order
    virtual void pay() const = 0;


    virtual void execute_iteration() = 0;

    virtual ~IClient() = 0;
};