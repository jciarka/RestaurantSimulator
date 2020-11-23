#pragma once
#include "IDish.h"
#include "TriggeredCounter.h"
#include "Raportable.h"


class DishBase : public TriggeredCounter, public Raportable, public IDish
{
private:
    static unsigned id_counter;
    static unsigned generate_unique_id();

    unsigned id;
    std::string name;
    price dish_price;
    unsigned preparing_time;
    unsigned eating_time;
    IDish::dish_state state;
    IKitchen* kitchen;
    IClient* client;

public:
    DishBase(unsigned preparing_time, unsigned eating_time, std::string name, IDish::dish_state state,
             price dish_price, ITrigger& global_trigger, IRaporter& global_raporter);

public:

    // general 
    virtual unsigned get_id() const override { return id; }
    virtual IDish::dish_state get_state() const override { return state; };
    virtual std::string get_name() const override { return name; }
  
    // Interface for IKitchen
    virtual void begin_preparing() override;
    virtual void set_kitchen(IKitchen* kitchen) override;

    virtual void OnCounted() override;

   
    // interface for IClient
    virtual void set_client(IClient* client) override;
    virtual void begin_eat() override;    
    virtual price get_price() override;

    virtual ~DishBase() {};
    
};
