#include "Façade.h"

Façade::Façade() : action_tokens(max_tokens_nb) {
	actions["fish"] = std::make_unique<FishingAction>(0);
	actions["row"] = std::make_unique<RowingAction>(0);
	data = std::make_unique<Data>(starting_fish_number);
}

const int Façade::getTokenNbr() {
	return action_tokens;
}

const int Façade::getDayCount() {
	return data->getDayCount();
}

const int Façade::getDistanceTravelled() {
	return data->getTravelledDistance();
}

void Façade::executeRowingAction(int const tokens) {
	actions["row"]->addTokens(tokens);
	data->travelDistance(actions["row"]->execute());
	actions["row"]->clearTokens();
}

void Façade::executeFishingAction(int const tokens) {
	actions["fish"]->addTokens(tokens);
	data->addFishes(actions["fish"]->execute());
	actions["fish"]->clearTokens();
}

void Façade::nextDay() {
	data->nextDay();
	//evnt = std::make_unique<>
	data->consumeFishes(fish_eating_number);

}

const int Façade::getFishCount() {
	return data->getFishCount();
}
