#include "WaitTimer.h"

WaitTimer::WaitTimer(int timer)
{
	this->tick = 0;
	this->timer = timer;
}

bool WaitTimer::update(bool resetOnok)
{
	tick++;
	bool isOk = isTimerOk();

	if (resetOnok && isOk)
	{
		resetTimer();
	}

	return isOk;
}

bool WaitTimer::isTimerOk()
{
	return tick >= timer;
}

void WaitTimer::resetTimer()
{
	tick = 0;
}
