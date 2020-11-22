#pragma once
#include <string>
#include <iostream>
#include "IRaporter.h"

class TerminaRaporter : public IRaporter
{
public:
	virtual void raport(std::string message) { std::cout << message << std::endl; };

	virtual ~TerminaRaporter() {};
};