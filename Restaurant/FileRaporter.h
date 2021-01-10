#pragma once
#include <string>
#include "IRaporter.h"

class FileRaporter : public IRaporter
{
public:
	virtual void raport(std::string message);

	virtual ~FileRaporter() {};
};