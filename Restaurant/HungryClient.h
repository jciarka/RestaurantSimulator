#pragma once

#pragma once
#include "fwd_include.h"

#include "StandardClient.h"
/*
#include "IClient.h"
#include "IGroup.h"

#include "DishBase.h"
#include "Beverage.h"
#include "MainCourse.h"
#include "TriggeredCounter.h"
#include "Raportable.h"
*/

class HungryClient : public StandardClient
{
protected:
    Soup* soup;
    // Container rod dishes that are delivered but beginned to eat
    std::vector<IDish*> waiting_dishes;

    // Functions to override in more specyfic clients
    virtual void choose_dishes();
    virtual std::vector<IOrder*> create_orders();
    virtual price count_total();


public:
    HungryClient(unsigned choosing_time, ITrigger* global_trigger, IRaporter* global_raporter);

    virtual void pick_up_order(IOrder* order) override;
    virtual void on_dish_state_change(IDish* dish) override;
    virtual ~HungryClient();
};