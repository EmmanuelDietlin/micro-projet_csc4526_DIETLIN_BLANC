#include "WindEvent.h"

/**
Execute l'Event. Emet un signal pour indiquer la distance perdue.
*/
void WindEvent::execute() {
	windEventSignal.emit();
	moveBackSignal.emit(moveBackDistance);
}