

#include <iostream>
#include "Order.h"
#include "Trigger.h"
#include "TerminalRaporter.h"
#include "StandardClient.h"
#include "TestMenu.h"
#include "TestGroup.h"
#include "TestKitchen.h"
#include "TestTable.h"
#include "Group.h"

void test1()
{
    Trigger trigger;
    TerminalRaporter raporter;
    TestGroup testgroup;
    TestTable testtable;
    StandardClient testclient (5, &trigger, &raporter);
    testclient.set_group(&testgroup);
    TestMenu testmenu(&trigger, &raporter);
    TestKitchen testkitchen;

    testclient.begin_feast();
    testclient.take_card(&testmenu);

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    std::vector<IDish*> dishes = testclient.give_order();

    dishes[0]->set_kitchen(&testkitchen);
    dishes[1]->set_kitchen(&testkitchen);

    dishes[0]->begin_preparing();
    dishes[1]->begin_preparing();

    for (size_t i = 0; i < 15; i++)
    {
        trigger.execute_iteration();
    }

    dishes[0]->deliver();
    dishes[1]->deliver();

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


