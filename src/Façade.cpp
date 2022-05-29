#include "Façade.h"

Façade::Façade() : action_tokens(max_tokens_nb) {
	actions["fish"] = std::move(std::make_unique<FishingAction>(0));
	actions["row"] = std::move(std::make_unique<RowingAction>(0));
}

const int Façade::getTokenNbr() {
	return action_tokens;
}

int Façade::addTokenToFishing() {
	if (action_tokens > 0) {
		actions["fish"]->addToken();
		action_tokens--;
	}
	return actions["fish"]->getTokenNb();
}

int Façade::addTokenToRowing() {
	if (action_tokens > 0) {
		actions["row"]->addToken();
		action_tokens--;
	}
	return actions["row"]->getTokenNb();
}

int Façade::removeTokenToFishing() {
	if (action_tokens < max_tokens_nb) {
		actions["fish"]->removeToken();
		action_tokens++;
	}
	return actions["fish"]->getTokenNb();
}

int Façade::removeTokenToRowing() {
	if (action_tokens < max_tokens_nb) {
		actions["row"]->removeToken();
		action_tokens++;
	}
	return actions["row"]->getTokenNb();
}
