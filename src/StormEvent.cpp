#include "StormEvent.h"

void StormEvent::execute() {
	stormEventSignal.emit();
	foodLostSignal.emit(foodLost);
	damageBoatSignal.emit(damageBoat);
}