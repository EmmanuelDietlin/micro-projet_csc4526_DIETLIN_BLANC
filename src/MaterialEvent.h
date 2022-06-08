#pragma once
#include "Event.h"

class MaterialEvent : public Event {
private:
	const int materialFound = 10;
public:
	vdk::signal<void(void)> materialEventSignal;
	vdk::signal<void(int const)> materialFoundSignal;
	void execute() override;
};