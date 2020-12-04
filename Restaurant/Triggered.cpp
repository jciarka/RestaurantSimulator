#include "Triggered.h"

Triggered::Triggered(ITrigger& trigger) : global_trigger_ptr(&trigger)
{
	trigger.add_iterated_object(this);
}

Triggered::Triggered(ITrigger* trigger) : global_trigger_ptr(trigger)
{
	trigger->add_iterated_object(this);
}

Triggered::~Triggered() 
{
	global_trigger_ptr->remove_iterated_object(this);
}
