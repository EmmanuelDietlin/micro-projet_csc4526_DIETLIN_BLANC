#include "MaterialEvent.h"

void MaterialEvent::execute() {
	materialEventSignal.emit();
	materialFoundSignal.emit(materialFound);
}