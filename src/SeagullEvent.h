#pragma once
#include "Event.h"

class SeagullEvent : public Event {
private:
	const int damagePlayer = 5;
	const int foodLost = 1;
public:
	vdk::signal<void(void)> seagullEventSignal;
	vdk::signal<void(int const)> damagePlayerSignal;
	vdk::signal<void(int const)> foodLostSignal;
	void execute() override;
};