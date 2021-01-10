
// Restaurant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Tests.h"
#include <string>
#include "RestaurantManager.h"

int main(int argc, char** argv)
{
    
    //test1();
    //test_hungry_client_1();
    //test_dessert_loving_client_1();
    //test_hungry_dessert_loving_client_1();
    //test2();
    //test3();
    //test_clients_queue();
    //test4();
    
    std::string filename0 = argv[1];
    std::string filename1 = argv[2];
    std::string filename2 = argv[3];
    std::string filename3 = argv[4];
    std::string filename4 = argv[5];
    std::string numer_of_waiters = argv[6];
    std::string filename5 = argv[7];
    //test5(filename0, filename1, filename2, filename3, filename4, numer_of_waiters, filename5);
    RestaurantManager restaurant(filename0, filename1, filename2, filename3, filename4, numer_of_waiters, filename5);
    for (int i = 0; i < 200; i++) 
    {
        restaurant.execute_iteration();
    }

    return 0;
}
