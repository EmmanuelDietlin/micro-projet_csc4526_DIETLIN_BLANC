#include "WindEvent.h"

/**
Execute l'Event. Emet un signal pour indiquer la distance perdue.
*/
void WindEvent::execute() {
	moveBackSignal.emit(moveBackDistance);
}