#include "Façade.h"
#include "FishingAction.h"
#include "RowingAction.h"
#include "HealPlayerAction.h"
#include "RepairBoatAction.h"
#include "StormEvent.h"
#include "WindEvent.h"
#include <random>
#include <fstream>
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
	std::ofstream recap("resources/recap.txt", std::ios::trunc);
	recapText << "Votre equipage s'est mutine, et vous voila maintenant abandonne sur une barque," <<
		"en plein milieu de l'ocean. Vous devez tenter de rejoindre l'ile de Timor, situee a" <<
		" 6700km de votre point de depart, en moins de 47 jours.\n Bonne chance..." << std::endl;
	recap << recapText.str();
	recap.close();
	recapText.str(std::string());
	connectDeathBoatToFaçade(boat.get());
	connectDeathPlayerToFaçade(player.get());
	eventVector.push_back(std::make_shared<StormEvent>());
	eventVector.push_back(std::make_shared<WindEvent>());
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
	int d = context->executeAction();
	distanceTravelled+= d;
	if (d > 0) {
		if (d < 200) {
			recapText << "Une combinaison de vents defavorables et de mer calme vous ont conduit a ne parcourir qu'une"
				<< " courte distance, diminuant donc vos chances de parvenir a votre objectif dans le temps imparti..." << std::endl;
		}
		else {
			recapText << "Des vents favorables et de bonnes decisions de votre part vous permettent de parcourir une grande distance."
				<< " A ce rythme, l'objectif sera surement atteint rapidement !" << std::endl;
		}
		recapText << std::endl << "Distance parcourue : " << d << " km" << std::endl << std::endl;

	}
}

/*
Execute l'action de pêcher, avec le nombre de jetons passé en paramètres
*/
void Façade::executeFishingAction(int const tokens) {
	context->setAction(std::make_unique<FishingAction>(tokens));
	int f = context->executeAction();
	fishCount+= f;
	if (f > 0) {
		if (f < 3) {
			recapText << "Vous avez lance votre ligne dans l'eau, mais la chance ne vous a pas sourit : seuls quelques malheureux"
				<< " poissons ont mordu a l'appat. Il va sans doute falloir vous rationner..." << std::endl;
		}
		else {
			recapText << "La chance vous a sourit : vous n'avez eu qu'a lancer votre ligne dans l'eau, et aussitot de nombreux"
				<< " poissons se sont jetes dessus ! Sacre festin en perspective !" << std::endl;
		}
		recapText << std::endl << "Poissons peches : " << f << std::endl << std::endl;
	}
	
}

/*
Execute l'action de se soigner, avec le nombre de jetons passé en paramètres
*/
void Façade::executeHealingAction(int const tokens) {
	context->setAction(std::make_unique<HealPlayerAction>(tokens));
	int p = context->executeAction();
	player->heal(p);
	if (p > 0) {
		recapText << "Un peu de repos ne fait pas de mal ! En vous reposant, vous avez pu recuperer"
			<< " une partie de votre energie" << std::endl;
		recapText << std::endl << "Vie : +" << p << std::endl << std::endl;
	}
}

/*
Execute l'action de réparer le bateau, avec le nombre de jetons passé en paramètres
*/
void Façade::executeRepairAction(int const tokens) {
	context->setAction(std::make_unique<RepairBoatAction>(tokens));
	int p = context->executeAction();
	boat->heal(p);
	if (p > 0) {
		recapText << "Reparer l'embarcation est une sage idee pour eviter de se retrouver au milieu"
			<< " de l'ocean accroche a une planche pour tenter de se maintenir a flot." << std::endl;
		recapText << std::endl << "Reparation : " << p << std::endl << std::endl;
	}
}

/*
Passe au jour suivant. Peut déclencher un évènement choisi de manière aléatoire, et 
consomme un certain nombre de poissons.
Ecrit également dans un fichier recap.txt le récapitulatif des actions et évènements.
*/
void Façade::nextDay(std::map<TokensType, int>& tokens) {
	recapText.str(std::string());
	dayCount++;
	executeFishingAction(tokens[TokensType::fishingsTokens]);
	executeRowingAction(tokens[TokensType::rowingTokens]);
	executeHealingAction(tokens[TokensType::healingTokens]);
	executeRepairAction(tokens[TokensType::repairTokens]);
	dailyEvent();
	fishCount -= fish_eating_number;
	if (fishCount < 0) {
		player->takeDamage(fishCount * damage_starvation * -1);
		fishCount = 0;
	}
	if (distanceTravelled >= maxDistance) {
		victory();
	}
	if (dayCount > maxDay) {
		defeat();
	}
	std::ofstream recap("resources/recap.txt", std::ios::trunc);
	recap << recapText.str() << std::endl;
	std::cout << recapText.str() << std::endl;
	recap.close();
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
		context->setEvent(eventVector[random_n_to_m(0, size - 1)]);
		context->executeEvent();
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
	distanceTravelled > distance ?  distanceTravelled - distance : 0;
	recapText << "Un vent violent souffle pendant toute la journee, vous faisant perdre une partie de "
		<< "votre progression !" << std::endl;
	recapText << std::endl << "Distance parcourue : -" << distance << "km" << std::endl << std::endl;
}

void Façade::loseFood(int const food) {
	fishCount > food ? fishCount - food : 0;
	recapText << "La tempete fait bringuebaler votre embarcation dans tous les sens, et "
		<< " une partie de vos provisions tombe par dessus bord !" << std::endl;
	recapText << std::endl << "Poissons : -" << food << std::endl << std::endl;
}

int Façade::random_n_to_m(int const nbMin, int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(nbMin, nbMax);
	return distribution(engine);
}