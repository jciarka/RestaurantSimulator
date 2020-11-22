#pragma once
#include <iostream>
#include <vector>

class IDish
{
    // pamiêtaj wskaŸnik IClient -> on_dish_state_change()
    // IKitchen -> on_dish_state_change()
public:
    enum class dish_state {
        ORDERED,
        PREPARATION,
        PREPARED,
        CONSUMPTION,
        EATEN,
    };

    virtual dish_state get_state() const = 0;

    // Interface for IKitchen
    virtual void begin_preparing() = 0;

    // interface for IClient
    virtual void begin_eat() = 0;

    virtual ~IDish() = 0;

};
