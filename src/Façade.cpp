#include "Façade.h"

Façade::Façade() : action_tokens(tokens_nb) {
	actions["fish"] = std::make_unique<FishingAction>(0);
	actions["row"] = std::make_unique<RowingAction>(0);
}

int Façade::getTokenNbr() {
	return action_tokens;
}

int Façade::addTokenToFishing() {
	if (action_tokens > 0) {
		actions["fish"]->addToken();
	}
	return actions["fish"]->getTokenNb();
}

int Façade::addTokenToRowing() {
	if (action_tokens > 0) {
		actions["row"]->addToken();
	}
	return actions["row"]->getTokenNb();
}
}