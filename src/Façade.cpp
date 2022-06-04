#include "Façade.h"
#include "FishingAction.h"
#include "RowingAction.h"
#include "HealPlayerAction.h"
#include "RepairBoatAction.h"
#include "StormEvent.h"
#include "WindEvent.h"
#include <random>

// à enlever après les tests de signals
#include <iostream>

/*
Constructeur de la façade. Prend en paramètres le nombre maximal de jours pour parcourir
la distance, la distance à parcourir dans le délai imparti, les points de vie de départ
du joueur, les points de vie de départ de l'embarcation.
*/
Façade::Façade(int const maxDay, int const maxDistance, int const playerHp, int const playerMaxHp,
	int const boatHp, int const boatMaxHp, ImGuiWindow* imguiWindow)
	: action_tokens(max_tokens_nb),
	fishCount(starting_fish_number), 
	maxDay(maxDay),
	maxDistance(maxDistance),
	imguiWindow(imguiWindow)
{
	boat = std::make_unique<Boat>(boatHp, boatMaxHp);
	player = std::make_unique<Player>("Player1", playerHp, playerMaxHp);
	context = std::make_unique<Context>();
	connectDeathBoatToFaçade(boat.get());
	connectDeathPlayerToFaçade(player.get());
	eventVector.push_back(std::make_unique<StormEvent>());
	eventVector.push_back(std::make_unique<WindEvent>());
	connectStormEventToFaçade((StormEvent *) eventVector[0].get());
	connectWindEventToFaçade((WindEvent *) eventVector[1].get());
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
Execute l'action de se soigner, avec le nombre de jetons passé en paramètres
*/
void Façade::executeHealingAction(int const tokens) {
	context->setAction(std::make_unique<HealPlayerAction>(tokens));
	player->heal(context->executeAction());
}

/*
Execute l'action de réparer le bateau, avec le nombre de jetons passé en paramètres
*/
void Façade::executeRepairAction(int const tokens) {
	context->setAction(std::make_unique<RepairBoatAction>(tokens));
	boat->heal(context->executeAction());
}

/*
Passe au jour suivant. Peut déclencher un évènement choisi de manière aléatoire, et 
consomme un certain nombre de poissons.
*/
void Façade::nextDay(std::map<TokensType, int>& tokens) {
	dayCount++;
	executeFishingAction(tokens[TokensType::fishingsTokens]);
	executeRowingAction(tokens[TokensType::rowingTokens]);
	executeHealingAction(tokens[TokensType::healingTokens]);
	executeRepairAction(tokens[TokensType::repairTokens]);
	dailyEvent();
	fishCount-= fish_eating_number;
	if (fishCount < 0) {
		player->takeDamage(fishCount * damage_starvation * -1);
		fishCount = 0;
	}
	if (distanceTravelled >= maxDistance) {
		victory();
	}
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

void Façade::newGame() {
	//à implémenter
}

void Façade::deathPlayer() {
	Façade::defeat();
}

void Façade::connectDeathPlayerToFaçade(Player* player) {
	player->deathSignal.connect(this, &Façade::deathPlayer);
}

void Façade::deathBoat() {
	Façade::defeat();
}

void Façade::connectDeathBoatToFaçade(Boat* boat) {
	boat->deathSignal.connect(this, &Façade::deathBoat);
}

void Façade::defeat() {
	*imguiWindow = ImGuiWindow::defeat;
}

void Façade::victory() {
	*imguiWindow = ImGuiWindow::victory;
}

void Façade::dailyEvent() {
	int probaDailyEvent = random_n_to_m(1, 100);
	std::cout << probaDailyEvent << std::endl;
	if (probaDailyEvent <= proba_event) {
		size_t size = eventVector.size();
		eventVector[random_n_to_m(0, size - 1)]->execute();
	}
}

void Façade::connectStormEventToFaçade(StormEvent* stormEvent) {
	stormEvent->damageBoatSignal.connect(boat.get(), &Entity::takeDamage);
	stormEvent->foodLostSignal.connect(this, &Façade::loseFood);
}

void Façade::connectWindEventToFaçade(WindEvent* windEvent) {
	windEvent->moveBackSignal.connect(this, &Façade::moveBack);
}

void Façade::moveBack(int const distance) {
	distanceTravelled -= distance;
}

void Façade::loseFood(int const food) {
	fishCount -= food;
}

int Façade::random_n_to_m(int const nbMin, int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(nbMin, nbMax);
	return distribution(engine);
}