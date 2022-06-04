#include "Fa�ade.h"
#include "FishingAction.h"
#include "RowingAction.h"
#include "HealPlayerAction.h"
#include "RepairBoatAction.h"
#include "StormEvent.h"
#include "WindEvent.h"
#include <random>

// � enlever apr�s les tests de signals
#include <iostream>

/*
Constructeur de la fa�ade. Prend en param�tres le nombre maximal de jours pour parcourir
la distance, la distance � parcourir dans le d�lai imparti, les points de vie de d�part
du joueur, les points de vie de d�part de l'embarcation.
*/
Fa�ade::Fa�ade(int const maxDay, int const maxDistance, int const playerHp, int const playerMaxHp,
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
	connectDeathBoatToFa�ade(boat.get());
	connectDeathPlayerToFa�ade(player.get());
	eventVector.push_back(std::make_unique<StormEvent>());
	eventVector.push_back(std::make_unique<WindEvent>());
	connectStormEventToFa�ade((StormEvent *) eventVector[0].get());
	connectWindEventToFa�ade((WindEvent *) eventVector[1].get());
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

/*
Execute l'action de ramer, avec le nombre de jetons pass� en param�tre
*/
void Fa�ade::executeRowingAction(int const tokens) {
	context->setAction(std::make_unique<RowingAction>(tokens));
	distanceTravelled+= context->executeAction();
}

/*
Execute l'action de p�cher, avec le nombre de jetons pass� en param�tres
*/
void Fa�ade::executeFishingAction(int const tokens) {
	context->setAction(std::make_unique<FishingAction>(tokens));
	fishCount+= context->executeAction();
}

/*
Execute l'action de se soigner, avec le nombre de jetons pass� en param�tres
*/
void Fa�ade::executeHealingAction(int const tokens) {
	context->setAction(std::make_unique<HealPlayerAction>(tokens));
	player->heal(context->executeAction());
}

/*
Execute l'action de r�parer le bateau, avec le nombre de jetons pass� en param�tres
*/
void Fa�ade::executeRepairAction(int const tokens) {
	context->setAction(std::make_unique<RepairBoatAction>(tokens));
	boat->heal(context->executeAction());
}

/*
Passe au jour suivant. Peut d�clencher un �v�nement choisi de mani�re al�atoire, et 
consomme un certain nombre de poissons.
*/
void Fa�ade::nextDay(std::map<TokensType, int>& tokens) {
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

int Fa�ade::getFishCount() {
	return fishCount;
}

int Fa�ade::getPlayerHp() {
	return player->getHp();
}

int Fa�ade::getBoatHp() {
	return boat->getHp();
}

void Fa�ade::newGame() {
	//� impl�menter
}

void Fa�ade::deathPlayer() {
	Fa�ade::defeat();
}

void Fa�ade::connectDeathPlayerToFa�ade(Player* player) {
	player->deathSignal.connect(this, &Fa�ade::deathPlayer);
}

void Fa�ade::deathBoat() {
	Fa�ade::defeat();
}

void Fa�ade::connectDeathBoatToFa�ade(Boat* boat) {
	boat->deathSignal.connect(this, &Fa�ade::deathBoat);
}

void Fa�ade::defeat() {
	*imguiWindow = ImGuiWindow::defeat;
}

void Fa�ade::victory() {
	*imguiWindow = ImGuiWindow::victory;
}

void Fa�ade::dailyEvent() {
	int probaDailyEvent = random_n_to_m(1, 100);
	std::cout << probaDailyEvent << std::endl;
	if (probaDailyEvent <= proba_event) {
		size_t size = eventVector.size();
		eventVector[random_n_to_m(0, size - 1)]->execute();
	}
}

void Fa�ade::connectStormEventToFa�ade(StormEvent* stormEvent) {
	stormEvent->damageBoatSignal.connect(boat.get(), &Entity::takeDamage);
	stormEvent->foodLostSignal.connect(this, &Fa�ade::loseFood);
}

void Fa�ade::connectWindEventToFa�ade(WindEvent* windEvent) {
	windEvent->moveBackSignal.connect(this, &Fa�ade::moveBack);
}

void Fa�ade::moveBack(int const distance) {
	distanceTravelled -= distance;
}

void Fa�ade::loseFood(int const food) {
	fishCount -= food;
}

int Fa�ade::random_n_to_m(int const nbMin, int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(nbMin, nbMax);
	return distribution(engine);
}