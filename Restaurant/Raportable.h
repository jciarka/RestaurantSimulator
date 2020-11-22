#pragma once
#include <string>
#include "IRaporter.h"
#include "IRaportable.h"

class Raportable : public IRaportable
{
private:
	IRaporter* global_raporter_ptr;

public:
	Raportable(IRaporter& global_raporter_ptr);
	virtual void raport(std::string message) override;
	virtual ~Raportable() { global_raporter_ptr = nullptr; };
};