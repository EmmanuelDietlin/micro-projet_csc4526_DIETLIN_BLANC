#include "FishingAction.h"

int FishingAction::execute(int const nbTokens) {
	return nbTokens * baseFishRate;
}