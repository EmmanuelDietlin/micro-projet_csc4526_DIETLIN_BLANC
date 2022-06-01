#include "Façade.h"

Façade::Façade(int const maxDay, int const maxDistance, int const playerHp, int const boatHp)
	: action_tokens(max_tokens_nb), fishCount(starting_fish_number), 
	maxDay(maxDay), maxDistance(maxDistance)
{
	boat = std::make_unique<Boat>(boatHp);
	player = std::make_unique<Player>("test", playerHp);
	context = std::make_unique<Context>();
}

int Façade::getTokenNbr() {
	return action_tokens;
}

int Façade::getDayCount() {
	return dayCount;
}

int Façade::getDistanceTravelled() {
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

int Façade::getFishCount() {
	return fishCount;
}

int Façade::getPlayerHp() {
	return player->getHp();
}

int Façade::getBoatHp() {
	return boat->getHp();
}
