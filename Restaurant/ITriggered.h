#pragma once

/// <summary>
/// Interfers dla obiektu subskrybuj¹cego zdarzenie z kalsy Trigger
/// Musi on definiowaæ funkcjê execute_iteration() wywo³ywan¹ przez klasê Trigger
/// </summary>


class ITriggered
{
public:
	virtual void execute_iteration() = 0;
	virtual ~ITriggered() = 0 {};
};