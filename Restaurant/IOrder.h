#pragma once

#include "fwd_include.h"

#include "IClient.h"
#include "IDish.h"

class IOrder
{
public:
    // Aviable states for client
    enum class order_state {
        ORDERED,
        PREPARATION,
        PREPARED
    };

    // interface methods
    virtual unsigned get_id() const = 0;
    virtual order_state get_state() const = 0;

    // Interfejs dla klienta
    virtual IDish* get_dish() = 0;
    virtual IClient* get_client() = 0;

    // Interface for kitchen
    virtual void begin_preparing() = 0;

    virtual ~IOrder() = 0 {};
};