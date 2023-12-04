#pragma once
class WaitTimer
{
private:
	int tick;
	int timer;

public:
	WaitTimer(int timer);

	bool update(bool resetOnok);
	bool isTimerOk();
	void resetTimer();
};

