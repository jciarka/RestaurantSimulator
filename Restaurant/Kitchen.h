#pragma once

#include "IKitchen.h"
#include "Raportable.h"
#include <queue>

class Kitchen :  public Raportable , public IKitchen
{
private:
    std::vector<IDish*> at_preparation;
    std::queue<IDish*> prepared;

public:
    Kitchen(IRaporter* global_raporter);
    virtual void take_order(IDish* order) override;
    virtual IDish* deliver_preapared() override;
    virtual void  on_dish_state_change(IDish* dish) override;

    virtual ~Kitchen() {};
};

