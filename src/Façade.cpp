#include "Fa�ade.h"

Fa�ade::Fa�ade() : action_tokens(max_tokens_nb) {
	actions["fish"] = std::make_unique<FishingAction>(0);
	actions["row"] = std::make_unique<RowingAction>(0);
	data = std::make_unique<Data>(starting_fish_number);
}

const int Fa�ade::getTokenNbr() {
	return action_tokens;
}

const int Fa�ade::getDayCount() {
	return data->getDayCount();
}

const int Fa�ade::getDistanceTravelled() {
	return data->getTravelledDistance();
}

void Fa�ade::executeRowingAction(int const tokens) {
	actions["row"]->addTokens(tokens);
	data->travelDistance(actions["row"]->execute());
	actions["row"]->clearTokens();
}

void Fa�ade::executeFishingAction(int const tokens) {
	actions["fish"]->addTokens(tokens);
	data->addFishes(actions["fish"]->execute());
	actions["fish"]->clearTokens();
}

void Fa�ade::nextDay() {
	data->nextDay();
	//evnt = std::make_unique<>
	data->consumeFishes(fish_eating_number);

}

const int Fa�ade::getFishCount() {
	return data->getFishCount();
}
