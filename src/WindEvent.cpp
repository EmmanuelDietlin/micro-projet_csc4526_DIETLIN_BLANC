#include "WindEvent.h"

void WindEvent::execute() {
	moveBackSignal.emit(moveBackDistance);
}