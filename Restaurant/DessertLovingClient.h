#pragma once

#include "fwd_include.h"
#include "StandardClient.h"

class DessertLovingClient : public StandardClient
{
protected:
    // Functions to override in more specyfic clients
    virtual void choose_dishes() override;

public:
    DessertLovingClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter);
    virtual ~DessertLovingClient() override {};

};