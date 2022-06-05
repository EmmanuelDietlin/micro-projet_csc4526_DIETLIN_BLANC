#include "UpgradeFishingAction.h"

int UpgradeFishingAction::execute() {
	return upgradeFactor;
}

UpgradeFishingAction::UpgradeFishingAction(int const tokenNb) : Action(tokenNb) {}