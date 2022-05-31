#include "Fa�ade.h"

Fa�ade::Fa�ade() : action_tokens(max_tokens_nb), 
				fishCount(starting_fish_number)
{
	boat = std::make_unique<Boat>(boatBaseHp);
	player = std::make_unique<Player>("test", playerBaseHp);
	context = std::make_unique<Context>();
}

const int Fa�ade::getTokenNbr() {
	return action_tokens;
}

const int Fa�ade::getDayCount() {
	return dayCount;
}

const int Fa�ade::getDistanceTravelled() {
	return distanceTravelled;
}

void Fa�ade::executeRowingAction(int const tokens) {
	context->setAction(std::make_unique<RowingAction>(tokens));
	distanceTravelled+= context->executeAction();
}

void Fa�ade::executeFishingAction(int const tokens) {
	context->setAction(std::make_unique<FishingAction>(tokens));
	fishCount+= context->executeAction();
}

void Fa�ade::nextDay() {
	dayCount++;
	//data->setEvent(std::make_unique<>());
	fishCount-= fish_eating_number;

}

const int Fa�ade::getFishCount() {
	return fishCount;
}
