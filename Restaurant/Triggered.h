#pragma once
#include "ITriggered.h"
#include "ITrigger.h"

/// The base class for the object subscribing to the event from the Trigger class
/// A constructor subscribe the event in the provided Trigger object
/// and a destructor removes this event from Trigger object
///
/// The inheriting class must define the execute_iteration () function called by the class Trigger

class Triggered : public ITriggered
{
protected:
	ITrigger* global_trigger_ptr;

public:
	Triggered(ITrigger& trigger);
	Triggered(ITrigger* trigger);
	~Triggered();

	virtual void execute_iteration() = 0; // Metoda do definicji w klasach pochodnych
};