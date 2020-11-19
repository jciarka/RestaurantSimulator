#pragma once
#include "ITriggered.h"

class ITrigger
{
public:
    virtual void execute_iteration() = 0; // Calls all handlers
    virtual void add_iterated_object(ITriggered* triggered_object) = 0;
    virtual void remove_iterated_object(ITriggered* triggered_object) = 0;
    virtual ~ITrigger() = 0;
};