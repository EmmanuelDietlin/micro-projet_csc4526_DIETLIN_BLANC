#include "StormEvent.h"

/**
Execute l'Event. Emet des signaux pour indiquer la quantit� de nourriture perdue
et les d�g�ts inflig�s au bateau.
*/
void StormEvent::execute() {
	stormEventSignal.emit();
	foodLostSignal.emit(foodLost);
	damageBoatSignal.emit(damageBoat);
}