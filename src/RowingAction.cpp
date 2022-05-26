#include "RowingAction.h"

int RowingAction::execute(int const nbTokens) {
	return nbTokens * baseDistance;
}