#pragma once
#include "Event.h"

/**
Classe représentant l'évènement de tempête
*/
class StormEvent : public Event {
private:
	const int damageBoat = 30;
	const int foodLost = 3;
public:
	vdk::signal<void(void)> stormEventSignal;
	vdk::signal<void(int const)> damageBoatSignal;
	vdk::signal<void(int const)> foodLostSignal;
	void execute() override;
};