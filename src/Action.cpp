#include "Action.h"

Action::Action(int const tokenNb) : tokenNb(tokenNb) {}

void Action::addToken() {
	tokenNb++;
}

void Action::removeToken() {
	if (tokenNb > 0) tokenNb--;
}

void Action::clearTokens() {
	tokenNb = 0;
}

int Action::getTokenNb() const {
	return tokenNb;
}
