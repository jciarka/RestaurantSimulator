
#include <iostream>
#include "Tests.h"
#include "Order.h"
#include "Trigger.h"
#include "TerminalRaporter.h"
#include "DessertLovingClient.h"
#include "TestMenu.h"
#include "TestGroup.h"
#include "TestKitchen.h"
#include "TestTable.h"
#include "Group.h"


void test_dessert_loving_client_1()
{
    Trigger trigger;
    TerminalRaporter raporter;
    TestGroup testgroup;
    TestTable testtable;
    TestMenu testmenu(&trigger, &raporter);
    TestKitchen testkitchen;

    DessertLovingClient testclient(5, &trigger, &raporter);
    testclient.set_group(&testgroup);
    testclient.begin_feast();
    testclient.take_card(&testmenu);

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    std::vector<IDish*> dishes = testclient.give_order();

    for (auto dish : dishes)
    {
        dish->set_kitchen(&testkitchen);
        dish->begin_preparing();
    }

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    for (auto dish : dishes)
    {
        dish->deliver();
    }

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }
    testclient.pay();

    for (size_t i = 0; i < 5; i++)
    {
        trigger.execute_iteration();
    }

}
