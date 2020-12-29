
// Restaurant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Tests.h"
#include <iostream>
#include <sstream>
#include "Order.h"
#include "Trigger.h"
#include "TerminalRaporter.h"
#include "StandardClient.h"
#include "HungryClient.h"
#include "DessertLovingClient.h"
#include "HungryDessertLovingClient.h"
#include "TestMenu.h"
#include "TestGroup.h"
#include "Kitchen.h"
#include "ServiceQueue.h"
#include "Waiter.h"
#include "Group.h"
#include "Table.h"
#include "GroupsQueue.h"

#include <cassert>  

void test_clients_queue()
{

    int j = 0;

    Trigger trigger;
    TerminalRaporter raporter;

    // Inicjacaj restauracji
    ServiceQueue servicequeue(&raporter);
    Kitchen kitchen(&raporter);
    TestMenu testmenu(&trigger, &raporter);
    Waiter waiter(&testmenu, &kitchen, &servicequeue, &trigger, &raporter);

    // Table for 10 people
    std::vector<ITable*> tables;
    tables.push_back(new Table(15, &trigger, &raporter));
    tables.push_back(new Table(15, &trigger, &raporter));
    tables.push_back(new Table(15, &trigger, &raporter));
    tables.push_back(new Table(15, &trigger, &raporter));
    tables.push_back(new Table(15, &trigger, &raporter));

    GroupQueue groups_queue(&tables, &trigger, &raporter);


    for (size_t i = 0; i < 100; i++)
    {
        std::unique_ptr<IGroup> Group1{ new Group(false, &servicequeue, &trigger, &raporter) };

        std::unique_ptr<IClient> testclient1 = std::make_unique<HungryClient>(5, &trigger, &raporter);
        Group1->add_client(std::move(testclient1));
        std::unique_ptr<IClient> testclient2 = std::make_unique<StandardClient>(6, &trigger, &raporter);
        Group1->add_client(std::move(testclient2));
        std::unique_ptr<IClient> testclient3 = std::make_unique<StandardClient>(7, &trigger, &raporter);
        Group1->add_client(std::move(testclient3));
        std::unique_ptr<IClient> testclient4 = std::make_unique<DessertLovingClient>(8, &trigger, &raporter);
        Group1->add_client(std::move(testclient4));
        std::unique_ptr<IClient> testclient5 = std::make_unique<DessertLovingClient>(8, &trigger, &raporter);
        Group1->add_client(std::move(testclient5));

        groups_queue.add_group(std::move(Group1));
    }

    // Wait and check if grups feezed and waiting for friends
    for (size_t i = 0; i < 500; i++)
    {
        trigger.execute_iteration();

        std::stringstream info;
        info << "---------------------------------------iter" << j++;
        raporter.raport(info.str());
    }


    for (auto table : tables)
    {
        delete table;
    }
}
