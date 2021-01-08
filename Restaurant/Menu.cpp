#include "Menu.h"
#include "CsvMenuReader.h"


Menu::Menu(std::vector<std::string> SoupArguments, std::vector<std::string> MainCourseArguments, std::vector<std::string> DessertArguments, std::vector<std::string> BeverageArguments, ITrigger* global_trigger, IRaporter* global_raporter)
	: Triggered(global_trigger), Raportable(global_raporter), SoupArguments(SoupArguments), MainCourseArguments(MainCourseArguments), DessertArguments(DessertArguments), BeverageArguments(BeverageArguments), global_trigger(global_trigger), global_raporter(global_raporter)
{}


Soup Menu::get_soup(unsigned index) const 
{
	std::string prepraring_time = SoupArguments[index];
	unsigned uns_prepraring_time = std::stoul(prepraring_time, nullptr, 10);
	std::string eating_time = SoupArguments[index + 1];
	unsigned uns_eating_time = std::stoul(eating_time, nullptr, 10);
	std::string dish_price = SoupArguments[index + 3];
	price price(std::stoul(dish_price, nullptr, 10));
	return Soup(uns_prepraring_time, uns_eating_time, SoupArguments[index + 2], price, global_trigger, global_raporter);
};
MainCourse Menu::get_main_course(unsigned index) const
{
	std::string prepraring_time = MainCourseArguments[index];
	unsigned uns_prepraring_time = std::stoul(prepraring_time, nullptr, 10);
	std::string eating_time = MainCourseArguments[index + 1];
	unsigned uns_eating_time = std::stoul(eating_time, nullptr, 10);
	std::string dish_price = MainCourseArguments[index + 3];
	price price(std::stoul(dish_price, nullptr, 10));
	return MainCourse(uns_prepraring_time, uns_eating_time, MainCourseArguments[index + 2], price, global_trigger, global_raporter);
};
Dessert Menu::get_dessert(unsigned index) const
{
	std::string prepraring_time = DessertArguments[index];
	unsigned uns_prepraring_time = std::stoul(prepraring_time, nullptr, 10);
	std::string eating_time = DessertArguments[index + 1];
	unsigned uns_eating_time = std::stoul(eating_time, nullptr, 10);
	std::string dish_price = DessertArguments[index + 3];
	price price(std::stoul(dish_price, nullptr, 10));
	return Dessert(uns_prepraring_time, uns_eating_time, DessertArguments[index + 2], price, global_trigger, global_raporter);
};
Beverage Menu::get_beverage(unsigned index) const
{
	std::string prepraring_time = BeverageArguments[index];
	unsigned uns_prepraring_time = std::stoul(prepraring_time, nullptr, 10);
	std::string eating_time = BeverageArguments[index + 1];
	unsigned uns_eating_time = std::stoul(eating_time, nullptr, 10);
	std::string dish_price = BeverageArguments[index + 3];
	price price(std::stoul(dish_price, nullptr, 10));
	return Beverage(uns_prepraring_time, uns_eating_time, BeverageArguments[index + 2], price, global_trigger, global_raporter);
};
unsigned Menu::get_soup_size() const
{
	return SoupArguments.size()/4;
};
unsigned Menu::get_main_course_size() const 
{
	return MainCourseArguments.size()/4;
};
unsigned Menu::get_dessert_size() const 
{
	return DessertArguments.size()/4;
};
unsigned Menu::get_beverage_size() const 
{
	return BeverageArguments.size()/4;
};

