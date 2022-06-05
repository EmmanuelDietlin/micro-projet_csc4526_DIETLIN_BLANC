#pragma once
#include "signals.h"

class Event {
public:
	explicit Event() = default;
	explicit Event(const Event&) = default;
	virtual ~Event() = default;
	virtual void execute() = 0;
};