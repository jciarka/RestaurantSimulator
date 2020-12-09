#pragma once

#include "fwd_include.h"
#include "StandardClient.h"

class HungryClient : public StandardClient
{
protected:
    // Functions to override in more specyfic clients
    virtual void choose_dishes() override;

public:
    HungryClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter);
    virtual ~HungryClient() override {};

};

/*
#include "StandardClient.h"

#include "IClient.h"
#include "IGroup.h"


class HungryClient : public StandardClient
{
protected:
    Soup* soup;

    // Functions to override in more specyfic clients
    virtual void choose_dishes();
    virtual std::vector<IDish*> create_orders();
    virtual price count_total();

public:
    HungryClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter);
    virtual void pick_up_order(IDish* order) override;
    virtual void on_dish_state_change(IDish* dish) override;
    virtual ~HungryClient();
};

*/