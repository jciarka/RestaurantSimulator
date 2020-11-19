#pragma once
#include <iostream>
#include <vector>
#include "IClient.h"

class IGroup
{
public:
    /*
    // Aviable states for client
    enum class group_state {
        QUEING,
        WAITING_FOR_CARD,
        CHOOSING_DISHES,
        READY_TO_ORDER,
        WAITING_FOR_DISHES,
        EATING,
        FINISHED_EATING,
        READY_TO_PAY,
    };
    */

    // typedef function type for raporting
    typedef void (*raport)(std::vector<std::ostream*>);

    // typedef state changed functions 
    typedef void (*group_state_changed_event_handler)(IClient* sender, IClient::client_state);

    //void add_client_state_changed_event_handler(group_state_changed_event_handler* event_handler);
    //void remove_client_state_changed_event_handler(group_state_changed_event_handler* event_handler);


    virtual unsigned get_id() const = 0;

    // interface for Kelner

    virtual void take_card(const IMenu* menu) = 0;
    virtual IClient::client_state get_state() const = 0; // common state of whole people in group

    virtual IOrder* give_order() const = 0; //Creates new Order 
                                            // and new Dishes (MUST REMEMBER TO delete the after eating)
    virtual void pick_up_order(IOrder* give_order()) = 0; //Deletes fullfilled order
    virtual void pay() const = 0;

    virtual void execute_iteration() = 0;

    virtual ~IGroup() = 0; // Delete clients 
};