#pragma once

class ITriggeredCounter
{
protected:
	virtual void OnCounted() = 0;

public:
	virtual void set_counter(unsigned value) = 0;
	virtual void start() = 0;
	virtual void pause() = 0;
	virtual bool is_counting() const = 0;
	virtual ~ITriggeredCounter() = 0;
};