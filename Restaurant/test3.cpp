
// Restaurant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Tests.h"
#include <iostream>
#include <sstream>
#include "Order.h"
#include "Trigger.h"
#include "TerminalRaporter.h"
#include "StandardClient.h"
#include "TestMenu.h"
#include "TestGroup.h"
#include "Kitchen.h"
#include "ServiceQueue.h"
#include "Waiter.h"
#include "Group.h"
#include "Table.h"

void test3()
{
    //test1();
    //test2();

    // Inicjacaj bazy

    Trigger trigger;
    TerminalRaporter raporter;

    // Inicjacaj restauracji
    ServiceQueue servicequeue(&raporter);
    Kitchen kitchen(&raporter);
    TestMenu testmenu(&trigger, &raporter);
    Waiter waiter(&testmenu, &kitchen, &servicequeue, &trigger, &raporter);
    Table table(6, &trigger, &raporter);

    // Inicjacja klientów
    IGroup* Group1 = new Group(false, &servicequeue, &trigger, &raporter);

    StandardClient* testclient1 = new StandardClient(5, &trigger, &raporter);
    Group1->add_client(testclient1);
    StandardClient* testclient2 = new StandardClient(6, &trigger, &raporter);
    Group1->add_client(testclient2);
    StandardClient* testclient3 = new StandardClient(7, &trigger, &raporter);
    Group1->add_client(testclient3);
    StandardClient* testclient4 = new StandardClient(8, &trigger, &raporter);
    Group1->add_client(testclient4);


    table.place_group(Group1);


    // Symulacja
    for (size_t i = 0; i < 100; i++)
    {
        trigger.execute_iteration();

        std::stringstream info;
        info << "---------------------------iter" << i;
        raporter.raport(info.str());
    }

    // Nic nie trzeba usuwaæ

    for (size_t i = 0; i < 5; i++)
    {
        trigger.execute_iteration();
    }
}
