#pragma once
#include "ITriggered.h"
#include "ITrigger.h"

/// <summary>
/// Klasa bazowa dla obiektu subskrybuj¹cego zdarzenie z kalsy Trigger
/// Defionowany jest konstruktor subskrybujacy zdarzenie z kalsy Trigger
/// i destruktor usuwaj¹cy to zdarzenie
/// 
/// Klasa dziedziczaca musi on definiowaæ funkcjê execute_iteration() wywo³ywan¹ przez klasê Trigger
/// </summary>

class Triggered : public ITriggered
{
protected:
	ITrigger* global_trigger_ptr;

public:
	Triggered(ITrigger& trigger);
	~Triggered();

	virtual void execute_iteration() = 0; // Metoda do definicji w klasach pochodnych
};