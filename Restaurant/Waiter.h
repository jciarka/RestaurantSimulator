#pragma once
#include "IWaiter.h"
#include "IKitchen.h"
#include "Triggered.h"
#include "Raportable.h"

class Waiter : public Triggered, public Raportable, public IWaiter
{
private:
    static unsigned id_counter;
    static unsigned generate_unique_id();

private:
    unsigned id;
    IServiceQueue* service_queue;
    IKitchen* kitchen;
    IMenu* menu;

public:
    Waiter(IMenu* menu, IKitchen* kitchen, IServiceQueue* service_queue, ITrigger* global_trigger, IRaporter* global_raporter);

    virtual unsigned get_id() const override;

    virtual void execute_iteration() override;

    virtual ~Waiter() override {};
};
