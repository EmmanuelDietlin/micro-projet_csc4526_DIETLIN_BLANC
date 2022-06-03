#include "RepairBoatAction.h"

RepairBoatAction::RepairBoatAction(int const tokenNb) : Action(tokenNb) {}

int RepairBoatAction::execute() {
	return repairFactor * tokenNb;
}