#include "Fa�ade.h"

Fa�ade::Fa�ade() : action_tokens(tokens_nb) {
	actions["fish"] = std::make_unique<FishingAction>(0);
	actions["row"] = std::make_unique<RowingAction>(0);
}

int Fa�ade::getTokenNbr() {
	return action_tokens;
}

int Fa�ade::addTokenToFishing() {
	if (action_tokens > 0) {
		actions["fish"]->addToken();
	}
	return actions["fish"]->getTokenNb();
}

int Fa�ade::addTokenToRowing() {
	if (action_tokens > 0) {
		actions["row"]->addToken();
	}
	return actions["row"]->getTokenNb();
}
}