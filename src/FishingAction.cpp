#include "FishingAction.h"

FishingAction::FishingAction(int const tokenNb) : Action(tokenNb) {}

int FishingAction::execute() {
	int f = 0;
	for (int i = 0; i < tokenNb; i++) {
		f += Action::random_int(0, 2);
	}
	return f ;
}