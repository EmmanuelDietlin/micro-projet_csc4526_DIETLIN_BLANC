#pragma once
#include "Event.h"

class StormEvent : public Event {
private:
	const int damageBoat = 20;
	const int foodLost = 2;
public:
	vdk::signal<void(void)> stormEventSignal;
	vdk::signal<void(int const)> damageBoatSignal;
	vdk::signal<void(int const)> foodLostSignal;
	void execute() override;
};