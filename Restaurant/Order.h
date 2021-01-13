#pragma once
#include "IOrder.h"


class Order : public IOrder
{
private:
    static unsigned id_counter;
    static unsigned generate_unique_id();

    unsigned id;
    IOrder::order_state state;
    IDish* dish;
    IClient* client;

public:
    Order(IDish* dish, IClient* client) : dish(dish), client(client), state(IOrder::order_state::ORDERED), 
                                          id(generate_unique_id()) {};

    virtual unsigned get_id() const override { return id; };
    virtual order_state get_state() const override { return state; };

    // Interface for Client
    virtual IDish* get_dish() override { return dish; };
    virtual IClient* get_client() override { return client; };

    // Interface for Kitchen
    virtual void begin_preparing() { dish->begin_preparing(); };


    virtual ~Order() {};
};
