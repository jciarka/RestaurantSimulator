#include "TriggeredCounter.h"

void TriggeredCounter::execute_iteration()
{
	if (is_counting())
	{
		if (count > 0)
		{
			--count;
			if (count == 0)
			{
				OnCounted();
			}
		}
	}
}
