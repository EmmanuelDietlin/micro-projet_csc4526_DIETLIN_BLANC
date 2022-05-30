#include "Fa�ade.h"

Fa�ade::Fa�ade() : action_tokens(max_tokens_nb) {
	actions["fish"] = 0;
	actions["row"] = 0;
	data = std::make_unique<Data>(starting_fish_number);
	context = std::make_unique<Context>();
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
	context->setAction(std::make_unique<RowingAction>(tokens));
	data->travelDistance(context->executeAction());
	actions["row"] = 0;
}

void Fa�ade::executeFishingAction(int const tokens) {
	context->setAction(std::make_unique<FishingAction>(tokens));
	data->addFishes(context->executeAction());
	actions["fish"] = 0;
}

void Fa�ade::nextDay() {
	data->nextDay();
	//data->setEvent(std::make_unique<>());
	data->consumeFishes(fish_eating_number);

}

const int Fa�ade::getFishCount() {
	return data->getFishCount();
}
