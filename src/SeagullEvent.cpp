#include "SeagullEvent.h"

void SeagullEvent::execute() {
	seagullEventSignal.emit();
	foodLostSignal.emit(foodLost);
	damagePlayerSignal.emit(damagePlayer);
}