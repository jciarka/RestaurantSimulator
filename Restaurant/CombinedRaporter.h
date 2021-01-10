#pragma once
#include <string>
#include "IRaporter.h"
#include "FileRaporter.h"
#include "TerminalRaporter.h"

class CombinedRaporter : public IRaporter
{
private:
	FileRaporter file;
	TerminalRaporter terminal;
public:
	virtual void raport(std::string message);

	virtual ~CombinedRaporter() {};
};