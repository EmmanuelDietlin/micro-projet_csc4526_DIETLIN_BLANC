#include "Fa�ade.h"

Fa�ade::Fa�ade(int const maxDay, int const maxDistance, int const playerHp, int const boatHp)
	: action_tokens(max_tokens_nb), fishCount(starting_fish_number), 
	maxDay(maxDay), maxDistance(maxDistance)
{
	boat = std::make_unique<Boat>(boatHp);
	player = std::make_unique<Player>("test", playerHp);
	context = std::make_unique<Context>();
}

int Fa�ade::getTokenNbr() {
	return action_tokens;
}

int Fa�ade::getDayCount() {
	return dayCount;
}

int Fa�ade::getDistanceTravelled() {
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

int Fa�ade::getFishCount() {
	return fishCount;
}

int Fa�ade::getPlayerHp() {
	return player->getHp();
}

int Fa�ade::getBoatHp() {
	return boat->getHp();
}
