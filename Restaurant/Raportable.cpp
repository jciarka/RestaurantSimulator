#include "Raportable.h"

Raportable::Raportable(IRaporter& global_raporter) : global_raporter_ptr(&global_raporter)
{}

Raportable::Raportable(IRaporter * global_raporter) : global_raporter_ptr(global_raporter)
{
}

void Raportable::raport(std::string message)
{
	global_raporter_ptr->raport(message);
}
