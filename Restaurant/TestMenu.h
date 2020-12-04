#pragma once

#include "IMenu.h"
#include "Triggered.h"
#include "Raportable.h"

class TestMenu : public Triggered, public Raportable, public IMenu
{
public:
    TestMenu(ITrigger* global_trigger, IRaporter* global_raporter) 
             : Triggered(global_trigger), Raportable(global_raporter)
    {}

    virtual void execute_iteration() override { };

    virtual Soup* get_soup(unsigned index) const override
    {
        return new Soup(5, 5, "Rosó³", price(2050), global_trigger_ptr, global_raporter_ptr);
    };

    virtual MainCourse* get_main_course(unsigned index) const override
    {
        return new MainCourse(5U, 5U, "Schamowy z frytkami", price(3050), global_trigger_ptr, global_raporter_ptr);
    };

    virtual Dessert* get_dessert(unsigned index) const override
    {
        return new Dessert(5U, 5U, "Tiramisu", price(1500), global_trigger_ptr, global_raporter_ptr);
    };

    virtual Beverage* get_beverage(unsigned index) const override
    {
        return new Beverage(2U, 10U, "Piwo", price(3050), global_trigger_ptr, global_raporter_ptr);
    };

    virtual unsigned get_soup_size() const override { return 10; };
    virtual unsigned get_main_course_size() const override { return 10; };
    virtual unsigned get_dessert_size() const override { return 10; };
    virtual unsigned get_beverage_size() const override { return 10; };
    virtual ~TestMenu()  {};
};
