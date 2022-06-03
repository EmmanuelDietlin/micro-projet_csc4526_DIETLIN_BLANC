#include "HealPlayerAction.h"

HealPlayerAction::HealPlayerAction(int const tokenNb) : Action(tokenNb) {}

int HealPlayerAction::execute() {
	return tokenNb * healFactor;
}
