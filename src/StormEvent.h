#pragma once
#include "Event.h"

/**
Classe repr�sentant l'�v�nement de temp�te
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