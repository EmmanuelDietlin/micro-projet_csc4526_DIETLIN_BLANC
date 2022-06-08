#include "StormEvent.h"

/**
Execute l'Event. Emet des signaux pour indiquer la quantité de nourriture perdue
et les dégâts infligés au bateau.
*/
void StormEvent::execute() {
	stormEventSignal.emit();
	foodLostSignal.emit(foodLost);
	damageBoatSignal.emit(damageBoat);
}