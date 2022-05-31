#include "Façade.h"

Façade::Façade() : action_tokens(max_tokens_nb), 
				fishCount(starting_fish_number)
{
	boat = std::make_unique<Boat>(boatBaseHp);
	player = std::make_unique<Player>("test", playerBaseHp);
	context = std::make_unique<Context>();
}

const int Façade::getTokenNbr() {
	return action_tokens;
}

const int Façade::getDayCount() {
	return dayCount;
}

const int Façade::getDistanceTravelled() {
	return distanceTravelled;
}

void Façade::executeRowingAction(int const tokens) {
	context->setAction(std::make_unique<RowingAction>(tokens));
	distanceTravelled+= context->executeAction();
}

void Façade::executeFishingAction(int const tokens) {
	context->setAction(std::make_unique<FishingAction>(tokens));
	fishCount+= context->executeAction();
}

void Façade::nextDay() {
	dayCount++;
	//data->setEvent(std::make_unique<>());
	fishCount-= fish_eating_number;

}

const int Façade::getFishCount() {
	return fishCount;
}
