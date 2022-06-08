#pragma once
#include "Event.h"

/**
Classe repr�sentant l'�v�nement de temp�te
*/
class StormEvent : public Event {
private:
	const int damageBoat = 20;
	const int foodLost = 2;
public:
	vdk::signal<void(int const)> damageBoatSignal;
	vdk::signal<void(int const)> foodLostSignal;
	void execute() override;
};