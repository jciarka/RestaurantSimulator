#pragma once

#include "fwd_include.h"
#include "Beverage.h"
#include "Soup.h"
#include "MainCourse.h"
#include "Dessert.h"


class IMenu
{
public:
    virtual Soup get_soup(unsigned index) const = 0; //Alokacja pamiêci, zwróc wskaŸnik
    virtual MainCourse get_main_course(unsigned index) const = 0; //Alokacja pamiêci, zwróc wskaŸnik
    virtual Dessert get_dessert(unsigned index) const = 0; //Alokacja pamiêci, zwróc wskaŸnik
    virtual Beverage get_beverage(unsigned index) const = 0; //Alokacja pamiêci, zwróc wskaŸnik
    virtual unsigned get_soup_size() const = 0;
    virtual unsigned get_main_course_size() const = 0;
    virtual unsigned get_dessert_size() const = 0;
    virtual unsigned get_beverage_size() const = 0; //Alokacja pamiêci, zwróc wskaŸnik
    virtual ~IMenu() = 0 {};
};