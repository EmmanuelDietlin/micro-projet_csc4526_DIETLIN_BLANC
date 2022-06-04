#include "StormEvent.h"

void StormEvent::execute() {
	foodLostSignal.emit(foodLost);
	damageBoatSignal.emit(damageBoat);
}