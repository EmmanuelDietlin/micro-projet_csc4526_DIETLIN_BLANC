#include "Fa�ade.h"

Fa�ade::Fa�ade() : action_tokens(max_tokens_nb) {
	actions["fish"] = std::move(std::make_unique<FishingAction>(0));
	actions["row"] = std::move(std::make_unique<RowingAction>(0));
}

const int Fa�ade::getTokenNbr() {
	return action_tokens;
}

int Fa�ade::addTokenToFishing() {
	if (action_tokens > 0) {
		actions["fish"]->addToken();
		action_tokens--;
	}
	return actions["fish"]->getTokenNb();
}

int Fa�ade::addTokenToRowing() {
	if (action_tokens > 0) {
		actions["row"]->addToken();
		action_tokens--;
	}
	return actions["row"]->getTokenNb();
}

int Fa�ade::removeTokenToFishing() {
	if (action_tokens < max_tokens_nb) {
		actions["fish"]->removeToken();
		action_tokens++;
	}
	return actions["fish"]->getTokenNb();
}

int Fa�ade::removeTokenToRowing() {
	if (action_tokens < max_tokens_nb) {
		actions["row"]->removeToken();
		action_tokens++;
	}
	return actions["row"]->getTokenNb();
}
