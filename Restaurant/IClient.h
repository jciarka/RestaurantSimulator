#pragma once

#include "fwd_include.h"

#include <vector>
#include "IMenu.h"
#include "IOrder.h"
#include "IDish.h"


class IClient
{
public:
    // Wska�niki
    // Menu
    // Wska�nik na dania
    // Wska�nik na grupe
    // Wska�nik na stolik 

    // Aviable states for client
    enum class client_state {
        WAITING_FOR_FRIENDS,
        WAITING_FOR_CARD,
        CHOOSING_DISHES,
        READY_TO_ORDER,
        WAITING_FOR_DISHES,
        EATING,
        FINISHED_EATING,
        LEAVING,
    };


    // general 
    virtual unsigned get_id() const = 0;
    virtual client_state get_state() const = 0;

    // Interface for IKelner
    virtual void take_card(const IMenu* menu) = 0;
    virtual std::vector<IOrder*> give_order() = 0; // Creates new Order 
                                            // and new Dishes (MUST REMEMBER TO delete the after eating)
    virtual void pick_up_order(IOrder* order) = 0; //Deletes fullfilled order
    virtual void pay() = 0;

    // Interfejs dla IDish
    virtual void on_dish_state_change(IDish* dish) = 0;

    // Interfejs dla IGroup
    virtual void begin_feast() = 0;

    virtual ~IClient() = 0 {};  // Zniszcz dania, zniszcz menu zniszcz zamowienia
};