#pragma once
#include "signals.h"

class Event {
public:
	explicit Event();
	virtual ~Event() = default;
	virtual void execute() = 0;
};