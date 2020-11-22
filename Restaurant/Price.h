#pragma once
#include <ostream>

class price
{
private:
	unsigned price_gr;

public:
	price(unsigned price_gr) : price_gr(price_gr) {};

	price operator+(const price& other) { return price(price_gr + other.price_gr); };

	friend std::ostream& operator<<(std::ostream& os, const price& price_to_print )
	{ 
		return os << price_to_print.price_gr / 100 << "zl " << price_to_print.price_gr % 100 << "gr";
	}
};

