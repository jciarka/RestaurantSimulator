
// Restaurant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Order.h"
#include "Trigger.h"
#include "TerminalRaporter.h"
#include "StandardClient.h"
#include "TestMenu.h"
#include "TestGroup.h"
#include "Kitchen.h"
#include "TestTable.h"

void test2()
{
    Trigger trigger;
    TerminalRaporter raporter;
    IGroup* testgroup = new TestGroup;
    Kitchen kitchen(&raporter);
    TestTable testtable;
    StandardClient* testclient = new StandardClient(5, &trigger, &raporter);
    testclient->set_group(testgroup);
    TestMenu testmenu(&trigger, &raporter);
    
    testclient->begin_feast();
    testclient->take_card(&testmenu);

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    std::vector<IOrder*> orders = testclient->give_order();
    for (auto order : orders)
    {
        kitchen.take_order(order);
    }
    orders.clear();

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    IOrder* order;
    order = kitchen.deliver_preapared();
    if (order != nullptr)
    {
        testclient->pick_up_order(order);
    }

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    order = kitchen.deliver_preapared();
    if (order != nullptr)
    {
        testclient->pick_up_order(order);
    }

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    testclient->pay();

    delete testclient;
    delete testgroup;

    for (size_t i = 0; i < 5; i++)
    {
        trigger.execute_iteration();
    }
}
