#pragma once
#include "ITriggeredCounter.h"
#include "Triggered.h"

class TriggeredCounter : public ITriggeredCounter, public Triggered
{
private:
	unsigned count;
	bool counting;

protected:
	virtual void OnCounted() = 0; //Metoda do definicji w klasie pochodnej

public:
	TriggeredCounter(ITrigger& trigger) : Triggered(trigger), count(0), counting(true) {};
	virtual ~TriggeredCounter() {};

	virtual void set_counter(unsigned value) override { count = value; };
	virtual void start() override { counting = true; };
	virtual void pause() override { counting = false; };
	virtual bool is_counting() const { return counting; };
	virtual void execute_iteration() override; // Redefinuj¹c metodê w klasach pochodnych koniecznie wywo³aæ metodê bazow¹!!
};