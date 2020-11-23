#include "Trigger.h"
#include <vector>
#include <stdexcept>

// Wywo³anie iteracji - wywo³¹nie ha¿dego z handlerów
void Trigger::execute_iteration()
{
	for (size_t i = 0; i < iterated_objects.size(); i++)
	{
		if (iterated_objects[i] != nullptr)
		{
			iterated_objects[i]->execute_iteration();
		}
	}

	// Add new objects
	while (objects_to_add.size() != 0)
	{
		ITriggered* triggered_object = objects_to_add[0];
		objects_to_add.erase(objects_to_add.begin());
		iterated_objects.push_back(triggered_object);
	}

	// Remove deleted objects
	auto position = std::find(iterated_objects.begin(), iterated_objects.end(), nullptr);
	while (position != iterated_objects.end())
	{
		iterated_objects.erase(position);
		position = std::find(iterated_objects.begin(), iterated_objects.end(), nullptr);
	}


	return;
}

void Trigger::add_iterated_object(ITriggered* triggered_object)
{

	std::vector<ITriggered*> objects_to_remove;
	if (triggered_object != nullptr)
	{
		objects_to_add.push_back(triggered_object);
	}
	else
	{
		throw std::invalid_argument("Iterated object is null");
	}
}

void Trigger::remove_iterated_object(ITriggered* triggered_object)
{
	auto object_to_remove = std::find(iterated_objects.begin(), iterated_objects.end(), triggered_object);
	if (object_to_remove != iterated_objects.end())
	{
		*object_to_remove = nullptr;
	}
}
