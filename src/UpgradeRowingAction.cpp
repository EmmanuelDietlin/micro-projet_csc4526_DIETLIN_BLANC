#include "UpgradeRowingAction.h"

int UpgradeRowingAction::execute() {
	return upgradeFactor;
}

UpgradeRowingAction::UpgradeRowingAction(int const tokenNb) : Action(tokenNb) {}
