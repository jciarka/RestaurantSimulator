#pragma once
#include "Tests.h"
// Restaurant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Order.h"
#include "Trigger.h"
#include "TerminalRaporter.h"
#include "StandardClient.h"
#include "TestMenu.h"
#include "TestGroup.h"
#include "TestKitchen.h"
#include "TestTable.h"

void test1()
{
    Trigger trigger;
    TerminaRaporter raporter;
    IGroup* testgroup = new TestGroup;
    TestTable testtable;
    StandardClient* testclient = new StandardClient(5, &trigger, &raporter);
    testclient->set_group(testgroup);
    TestMenu testmenu(&trigger, &raporter);
    TestKitchen testkitchen;

    testclient->begin_feast();
    testclient->take_card(&testmenu);

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    std::vector<IOrder*> orders = testclient->give_order();

    orders[0]->get_dish()->set_kitchen(&testkitchen);
    orders[1]->get_dish()->set_kitchen(&testkitchen);

    orders[0]->get_dish()->begin_preparing();
    orders[1]->get_dish()->begin_preparing();

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    testclient->pick_up_order(orders[0]);
    testclient->pick_up_order(orders[1]);

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


