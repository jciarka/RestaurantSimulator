#pragma once
#include <iostream>
#include <vector>
#include "IDish.h"
#include "IMenu.h"
#include "IOrder.h"

class IClient
{
public:
    // Wskaüniki
    // Menu
    // Wskaünik na dania
    // Wskaünik na grupe
    // Wskaünik na stolik 

    // Aviable states for client
    enum class client_state {
        WAITING_FOR_FRIENDS,
        WAITING_FOR_CARD,
        CHOOSING_DISHES,
        READY_TO_ORDER,
        WAITING_FOR_DISHES,
        EATING,
        FINISHED_EATING,
        READY_TO_PAY,
        LEAVING,
    };


    // general 
    virtual unsigned get_id() const = 0;
    virtual client_state get_state() const = 0;

    // Interface for IKelner
    virtual void take_card(const IMenu* menu) = 0;
    virtual std::vector<IOrder*> give_order() const = 0; // Creates new Order 
                                            // and new Dishes (MUST REMEMBER TO delete the after eating)
    virtual void pick_up_order(IOrder* order) = 0; //Deletes fullfilled order
    virtual void pay() const = 0;

    // Interfejs dla IDish
    virtual bool on_dish_state_change(IDish* dish) = 0;

    // Interfejs dla IGroup
    virtual void begin_feast() = 0;

    virtual ~IClient() = 0;  // Zniszcz dania, zniszcz menu zniszcz zamowienia
};