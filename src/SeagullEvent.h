#pragma once
#include "Event.h"

class SeagullEvent : public Event {
private:
	const int damagePlayer = 10;
	const int foodLost = 2;
public:
	vdk::signal<void(void)> seagullEventSignal;
	vdk::signal<void(int const)> damagePlayerSignal;
	vdk::signal<void(int const)> foodLostSignal;
	void execute() override;
};