#include "Action.h"

Action::Action(int const tokenNb) : tokenNb(tokenNb) {}

void Action::addTokens(int const tokens) {
	tokenNb = tokens;
}


void Action::clearTokens() {
	tokenNb = 0;
}

int Action::getTokenNb() const {
	return tokenNb;
}
