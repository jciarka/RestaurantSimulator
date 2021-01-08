#pragma once
#include "fwd_include.h"
#include <iostream>

class IWaiter
{
public:
    virtual ~IWaiter() = 0 {};

    virtual unsigned get_id() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const IWaiter& waiter);
};