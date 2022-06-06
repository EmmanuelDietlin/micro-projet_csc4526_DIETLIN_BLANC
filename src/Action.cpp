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

/*
Generates a random int between start and end, chosen using a uniform distribution.
*/
int Action::random_int(int const start, int const end) {
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(start, end);
	return distribution(engine);
}
