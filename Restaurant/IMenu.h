#pragma once
#include <iostream>

class IMenu
{
public:
    virtual IDish* get_soup(unsigned index) = 0; //Alokacja pami�ci, zwr�c wska�nik
    virtual IDish* get_main_course(unsigned index) = 0; //Alokacja pami�ci, zwr�c wska�nik
    virtual IDish* get_dessert(unsigned index) = 0; //Alokacja pami�ci, zwr�c wska�nik
    virtual unsigned get_soup_size() = 0;
    virtual unsigned get_main_size() = 0;
    virtual unsigned get_dessert_size() = 0;
    virtual ~IMenu() = 0 {};
};