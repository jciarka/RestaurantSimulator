#include "Trigger.h"
#include <stdexcept>

// Wywo³anie iteracji - wywo³¹nie ha¿dego z handlerów
void Trigger::execute_iteration()
{
	for (auto iterated_object : iterated_objects)
	{
		if (iterated_object != nullptr)
		{
			iterated_object->execute_iteration();
		}
	}
	return;
}

void Trigger::add_iterated_object(ITriggered* triggered_object)
{
	if (triggered_object != nullptr)
	{
		iterated_objects.push_back(triggered_object);
	}
	else
	{
		throw std::invalid_argument("Iterated object is null");
	}
}

void Trigger::remove_iterated_object(ITriggered* triggered_object)
{
	auto position = std::find(iterated_objects.begin(), iterated_objects.end(), triggered_object);
	if (position != iterated_objects.end())
		iterated_objects.erase(position);
}
