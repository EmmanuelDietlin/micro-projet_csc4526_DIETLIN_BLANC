#include "RowingAction.h"

RowingAction::RowingAction(int const tokenNb) : Action(tokenNb) {}

int RowingAction::execute() {
	return (tokenNb + Action::random_int(-1, 1)) * baseDistance ;
}