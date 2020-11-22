#pragma once
#include <string>

class IRaportable
{
public:
	virtual void raport(std::string message) = 0;
	virtual ~IRaportable() = 0 {};
};