#include "Façade.h"

/*
Constructeur de la façade. Prend en paramètres le nombre maximal de jours pour parcourir
la distance, la distance à parcourir dans le délai imparti, les points de vie de départ
du joueur, les points de vie de départ de l'embarcation.
*/
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

/*
Execute l'action de ramer, avec le nombre de jetons passé en paramètre
*/
void Façade::executeRowingAction(int const tokens) {
	context->setAction(std::make_unique<RowingAction>(tokens));
	distanceTravelled+= context->executeAction();
}

/*
Execute l'action de pêcher, avec le nombre de jetons passé en paramètres
*/
void Façade::executeFishingAction(int const tokens) {
	context->setAction(std::make_unique<FishingAction>(tokens));
	fishCount+= context->executeAction();
}

/*
Passe au jour suivant. Peut déclencher un évènement choisi de manière aléatoire, et 
consomme un certain nombre de poissons.
*/
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
