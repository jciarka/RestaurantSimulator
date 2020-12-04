#pragma once

#include "fwd_include.h"
#include "Beverage.h"
#include "Soup.h"
#include "MainCourse.h"
#include "Dessert.h"


class IMenu
{
public:
    virtual Soup get_soup(unsigned index) const = 0; //Alokacja pami�ci, zwr�c wska�nik
    virtual MainCourse get_main_course(unsigned index) const = 0; //Alokacja pami�ci, zwr�c wska�nik
    virtual Dessert get_dessert(unsigned index) const = 0; //Alokacja pami�ci, zwr�c wska�nik
    virtual Beverage get_beverage(unsigned index) const = 0; //Alokacja pami�ci, zwr�c wska�nik
    virtual unsigned get_soup_size() const = 0;
    virtual unsigned get_main_course_size() const = 0;
    virtual unsigned get_dessert_size() const = 0;
    virtual unsigned get_beverage_size() const = 0; //Alokacja pami�ci, zwr�c wska�nik
    virtual ~IMenu() = 0 {};
};