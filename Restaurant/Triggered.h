#pragma once
#include "ITriggered.h"
#include "ITrigger.h"

/// <summary>
/// Klasa bazowa dla obiektu subskrybuj�cego zdarzenie z kalsy Trigger
/// Defionowany jest konstruktor subskrybujacy zdarzenie z kalsy Trigger
/// i destruktor usuwaj�cy to zdarzenie
/// 
/// Klasa dziedziczaca musi on definiowa� funkcj� execute_iteration() wywo�ywan� przez klas� Trigger
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