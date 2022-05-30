#include "Façade.h"

Façade::Façade() : action_tokens(max_tokens_nb) {
	actions["fish"] = 0;
	actions["row"] = 0;
	data = std::make_unique<Data>(starting_fish_number);
	context = std::make_unique<Context>();
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
	context->setAction(std::make_unique<RowingAction>(tokens));
	data->travelDistance(context->executeAction());
	actions["row"] = 0;
}

void Façade::executeFishingAction(int const tokens) {
	context->setAction(std::make_unique<FishingAction>(tokens));
	data->addFishes(context->executeAction());
	actions["fish"] = 0;
}

void Façade::nextDay() {
	data->nextDay();
	//data->setEvent(std::make_unique<>());
	data->consumeFishes(fish_eating_number);

}

const int Façade::getFishCount() {
	return data->getFishCount();
}
