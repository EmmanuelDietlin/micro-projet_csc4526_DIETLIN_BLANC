#pragma once
#include "Event.h"

/**
Classe représentant l'évènement "vent"

*/
class WindEvent : public Event {
private:
	const int moveBackDistance = 50;
public:
	vdk::signal<void(void)> windEventSignal;
	vdk::signal<void(int const)> moveBackSignal;
	void execute() override;
};