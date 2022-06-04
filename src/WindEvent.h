#pragma once
#include "Event.h"

class WindEvent : public Event {
private:
	const int moveBackDistance = 50;
public:
	vdk::signal<void(int const)> moveBackSignal;
	void execute() override;
};