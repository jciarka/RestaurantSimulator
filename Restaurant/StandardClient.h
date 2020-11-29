#pragma once
#include "fwd_include.h"

#include "IClient.h"
#include "IGroup.h"

#include "DishBase.h"
#include "Beverage.h"
#include "MainCourse.h"
#include "TriggeredCounter.h"
#include "Raportable.h"


class StandardClient : public TriggeredCounter, public Raportable, public IClient
{
private:
    static unsigned id_counter;
    static unsigned generate_unique_id();

    IClient::client_state state;
    unsigned id;
    unsigned choosing_time;
    const IMenu* menu;
    // std::vector<IDish*> dishes;
    Beverage* beveage;
    MainCourse* main_course;
    IGroup* group;  // Na potrzeby wypisywania
    ITable* table;  // Na potrzeby wypisywania

    virtual void choose_dishes(); // Bêdzie modyfikowana klasach potomnych
    virtual std::vector<IOrder*> create_orders();
    virtual price count_total();

protected:
    virtual void OnCounted() override; //Logika odliczania

public:
    StandardClient(unsigned choosing_time, ITrigger& global_trigger, IRaporter& global_raporter);

    virtual unsigned get_id() const override { return id; };
    virtual client_state get_state() const override { return state; };
    
    // Interfejs dla IGroup
    virtual void begin_feast() override;
    virtual void set_group(IGroup* group) override;

    // Interface for IKelner
    virtual void take_card(const IMenu* menu) override;
    virtual std::vector<IOrder*> give_order() override; // Creates new Order 
                                            // and new Dishes (MUST REMEMBER TO delete the after eating)
    virtual void pick_up_order(IOrder* order) override;

    // Interfejs dla IDish
    virtual void on_dish_state_change(IDish* dish) override;

    virtual void pay() override;

    virtual ~StandardClient();// Zniszcz dania, zniszcz menu 
};