#include "RowingAction.h"

RowingAction::RowingAction(int const tokenNb) : Action(tokenNb) {}

int RowingAction::execute() {
	return tokenNb * baseDistance;
}