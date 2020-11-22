#pragma once
#include <string>

class IRaporter
{
public:
	virtual void raport(std::string message) = 0;

	virtual ~IRaporter() = 0 {};
};