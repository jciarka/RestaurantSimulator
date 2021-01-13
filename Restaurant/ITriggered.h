#pragma once

// Interface for the object subscribing the Trigger event
// It must define an execute_iteration () function called by the class Trigger

class ITriggered
{
public:
	virtual void execute_iteration() = 0;
	virtual ~ITriggered() = 0 {};
};