
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

#include <cassert>  

void test3()
{
    /// <summary>
    /// During test two groups are created:
    ///  1. First oone has 4 people - waiting for second grup
    ///  2. Second group has 5 people - ready to order
    /// 
    /// Group will be posed at 10 seats table
    /// 
    /// 
    /// Expected behavior - group first won start befor second grup joins
    /// </summary>
    /// 
    /// 
    int j = 0;

    Trigger trigger;
    TerminalRaporter raporter;

    // Inicjacaj restauracji
    ServiceQueue servicequeue(&raporter);
    Kitchen kitchen(&raporter);
    TestMenu testmenu(&trigger, &raporter);
    Waiter waiter(&testmenu, &kitchen, &servicequeue, &trigger, &raporter);

    // Table for 10 people
    Table table(10, &trigger, &raporter);

    // Table for 11 people
    Table table_prim(11, &trigger, &raporter);

        for (size_t cycle = 0; cycle < 3; cycle++)
        {

        ///
        /// Creation of first group that is waiting for friends
        /// Contains 4 people
        /// placed at table 1 for 10 people
        /// 

        std::unique_ptr<IGroup> Group1{ new Group(true, &servicequeue, &trigger, &raporter) };

        std::unique_ptr<IClient> testclient1 = std::make_unique<StandardClient>(5, &trigger, &raporter);
        Group1->add_client(std::move(testclient1));
        std::unique_ptr<IClient> testclient2 = std::make_unique<StandardClient>(6, &trigger, &raporter);
        Group1->add_client(std::move(testclient2));
        std::unique_ptr<IClient> testclient3 = std::make_unique<StandardClient>(7, &trigger, &raporter);
        Group1->add_client(std::move(testclient3));
        std::unique_ptr<IClient> testclient4 = std::make_unique<StandardClient>(8, &trigger, &raporter);
        Group1->add_client(std::move(testclient4));

        table.place_group(std::move(Group1));

        ///
        /// Creation of another group (prim) identical to Group1
        /// Contains 4 people
        /// Placed at table1_prim for 11 people - bigger then table1
        /// 

        std::unique_ptr<IGroup> Group1_prim { new Group(true, &servicequeue, &trigger, &raporter) };

        std::unique_ptr<IClient> testclient1_prim = std::make_unique<StandardClient>(5, &trigger, &raporter);
        Group1_prim->add_client(std::move(testclient1_prim));
        std::unique_ptr<IClient> testclient2_prim = std::make_unique<StandardClient>(6, &trigger, &raporter);
        Group1_prim->add_client(std::move(testclient2_prim));
        std::unique_ptr<IClient> testclient3_prim = std::make_unique<StandardClient>(7, &trigger, &raporter);
        Group1_prim->add_client(std::move(testclient3_prim));
        std::unique_ptr<IClient> testclient4_prim = std::make_unique<StandardClient>(8, &trigger, &raporter);
        Group1_prim->add_client(std::move(testclient4_prim));

        table_prim.place_group(std::move(Group1_prim));

        // Wait and check if grups feezed and waiting for friends
        for (size_t i = 0; i < 10; i++)
        {
            trigger.execute_iteration();

            std::stringstream info;
            info << "---------------------------------------iter" << j++;
            raporter.raport(info.str());
        }


        // Creation of second group also waiting for friends that will try to join group1 and group1_prim
        // Contains 6 people
        std::unique_ptr<IGroup> Group2_prim{ new Group(true /*Group waiting for friends*/, &servicequeue, &trigger, &raporter) };

        Group2_prim->add_client(std::move(std::make_unique<StandardClient>(3, &trigger, &raporter)));
        Group2_prim->add_client(std::move(std::make_unique<StandardClient>(2, &trigger, &raporter)));
        Group2_prim->add_client(std::move(std::make_unique<StandardClient>(7, &trigger, &raporter)));
        Group2_prim->add_client(std::move(std::make_unique<StandardClient>(1, &trigger, &raporter)));
        Group2_prim->add_client(std::move(std::make_unique<StandardClient>(1, &trigger, &raporter)));
        Group2_prim->add_client(std::move(std::make_unique<StandardClient>(1, &trigger, &raporter)));


        // At table 4 of 10 seats occupied
        // Group2_prim should not be able to joing Group1 - even if enough space because after merge
        // result group will be still waiting for friends and there will be no place for third group to join
        // There must be one more seat at table

        // Can't join group1
        assert(!table.can_place_group(Group2_prim.get()));

        // At table_prim 4 of 11 seats occupied
        // Graup2_prim can join group1_prim, because table has one place more
        assert(table_prim.can_place_group(Group2_prim.get()));

        if (table_prim.can_place_group(Group2_prim.get()))
        {
            table_prim.place_group(std::move(Group2_prim));
        }

        ///_____________________________________________________________________________________
        /// Creation of second group ready to order that is going to join group1
        /// Contains 5 people
        /// 

        std::unique_ptr<IGroup> Group2{ new Group(false, &servicequeue, &trigger, &raporter) };
        std::unique_ptr<IClient> testclient5 = std::make_unique<StandardClient>(3, &trigger, &raporter);
        Group2->add_client(std::move(testclient5));
        std::unique_ptr<IClient> testclient6 = std::make_unique<StandardClient>(2, &trigger, &raporter);
        Group2->add_client(std::move(testclient6));
        std::unique_ptr<IClient> testclient7 = std::make_unique<StandardClient>(7, &trigger, &raporter);
        Group2->add_client(std::move(testclient7));
        std::unique_ptr<IClient> testclient8 = std::make_unique<StandardClient>(1, &trigger, &raporter);
        Group2->add_client(std::move(testclient8));
        std::unique_ptr<IClient> testclient9 = std::make_unique<StandardClient>(1, &trigger, &raporter);
        Group2->add_client(std::move(testclient9));

        // Can't join group1_prim - group much to big
        assert(!table_prim.can_place_group(Group2.get()));

        // But can join join group1, just enough seats
        assert(table.can_place_group(Group2.get()));

        // check if can_place_group group2
        // use get() not to lose group2 concrete object ownership
        if (table.can_place_group(Group2.get()))
        {
            table.place_group(std::move(Group2));
        }

        // Wait some period
        for (size_t i = 0; i < 10; i++)
        {
            trigger.execute_iteration();

            std::stringstream info;
            info << "---------------------------------------iter" << j++;
            raporter.raport(info.str());
        }

        // Check grup states

        ///_____________________________________________________________________________________
        /// Creation of third group - one person that group2_prim is waitung for
        /// 

        std::unique_ptr<IGroup> Group3_prim{ new Group(false, &servicequeue, &trigger, &raporter) };
        Group3_prim->add_client(std::make_unique<StandardClient>(3, &trigger, &raporter));

        // Can't place with group that has beginned 
        assert(!table.can_place_group(Group3_prim.get()));
        // Can't place with group that has beginned 
        assert(table_prim.can_place_group(Group3_prim.get()));

        if (table_prim.can_place_group(Group3_prim.get()))
        {
            table_prim.place_group(std::move(Group3_prim));
        }



        // Symulation
        for (size_t i = 0; i < 100; i++)
        {
            trigger.execute_iteration();

            std::stringstream info;
            info << "---------------------------iter" << j++;
            raporter.raport(info.str());
        }

        // In this place group 1 should be disposed
        // table should be empty
        assert(table.is_available());

        for (size_t i = 0; i < 5; i++)
        {
            trigger.execute_iteration();
        }

    }
}
