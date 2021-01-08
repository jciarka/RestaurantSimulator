#pragma once

#include "IMenu.h"
#include "Triggered.h"
#include "Raportable.h"
#include <vector>
#include "CsvMenuReader.h"

class Menu : public Triggered, public Raportable, public IMenu
{
private:
    std::vector<std::string> SoupArguments;
    std::vector<std::string> MainCourseArguments;
    std::vector<std::string> DessertArguments;
    std::vector<std::string> BeverageArguments;
    ITrigger* global_trigger;
    IRaporter* global_raporter;
public:
    Menu(std::vector<std::string> SoupArguments, std::vector<std::string> MainCourseArguments, std::vector<std::string> DessertArguments, std::vector<std::string> BeverageArguments, ITrigger* global_trigger, IRaporter* global_raporter);
    void execute_iteration() override {};
    Soup get_soup(unsigned index) const override;
    MainCourse get_main_course(unsigned index) const override;
    Dessert get_dessert(unsigned index) const override;
    Beverage get_beverage(unsigned index) const override;
    unsigned get_soup_size() const override;
    unsigned get_main_course_size() const override;
    unsigned get_dessert_size() const override;
    unsigned get_beverage_size() const override;
    virtual ~Menu() {};
};
