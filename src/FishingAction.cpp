#include "FishingAction.h"

FishingAction::FishingAction(int const tokenNb) : Action(tokenNb) {}

int FishingAction::execute() {
	return tokenNb * baseFishRate;
}