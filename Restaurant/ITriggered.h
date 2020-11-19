#pragma once

/// <summary>
/// Interfers dla obiektu subskrybuj�cego zdarzenie z kalsy Trigger
/// Musi on definiowa� funkcj� execute_iteration() wywo�ywan� przez klas� Trigger
/// </summary>


class ITriggered
{
public:
	virtual void execute_iteration() = 0;
	virtual ~ITriggered() = 0 {};
};