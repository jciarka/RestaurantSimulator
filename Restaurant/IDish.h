#pragma once

#include "fwd_include.h"

#include <string>
#include "Price.h"


class IDish
{
    // pamiêtaj wskaŸnik IClient -> on_dish_state_change()
    // IKitchen -> on_dish_state_change()

public:
    enum class dish_state {
        CHOOSEN,
        PREPARATION,
        PREPARED,
        DELIVERED,
        CONSUMPTION,
        EATEN,
    };

    // general 
    virtual unsigned get_id() const = 0;
    virtual dish_state get_state() const = 0;
    virtual std::string get_name() const = 0;

    // Interface for IKitchen
    virtual void set_kitchen(IKitchen* kitchen) = 0;
    virtual void begin_preparing() = 0;

    // interface for IClient
    virtual void set_client(IClient* client) = 0;
    virtual void deliver() = 0;
    virtual void begin_eat() = 0;
    virtual std::string to_string() const = 0;
    virtual price get_price() = 0;

    virtual ~IDish() = 0 {};

    //friend std::ostream& operator<<(std::ostream& os, const IDish& dish) { return os << dish.to_string(); }
};
