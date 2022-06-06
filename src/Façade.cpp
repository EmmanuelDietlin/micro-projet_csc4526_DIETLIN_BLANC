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
	int const boatHp, int const boatMaxHp, int const materials)
	: action_tokens(max_tokens_nb),
	fishCount(starting_fish_number), 
	maxDay(maxDay),
	maxDistance(maxDistance),
	materials(materials)
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
	eventVector.push_back(std::make_shared<StormEvent>());
	eventVector.push_back(std::make_shared<WindEvent>());	
	connectStormEventToFaçade((StormEvent*)eventVector[0].get());
	connectWindEventToFaçade((WindEvent*)eventVector[1].get()); 
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
	int d = rowingBonus;
	if (tokens > 0) {
		context->setAction(std::make_unique<RowingAction>(tokens));
		d += context->executeAction();
	}
	distanceTravelled.fetch_add(d);
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
	int f = fishingBonus;
	if (tokens > 0) {
		context->setAction(std::make_unique<FishingAction>(tokens));
		f = context->executeAction();
	}
	fishCount.fetch_add(f);
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
	if (tokens > 0) {
		context->setAction(std::make_unique<HealPlayerAction>(tokens));
		int h = context->executeAction();
		player->heal(h);
		recapText << "Un peu de repos ne fait pas de mal ! En vous reposant, vous avez pu recuperer"
			<< " une partie de votre energie" << std::endl;
		recapText << std::endl << "Vie : +" << h << std::endl << std::endl;
	}
}

/*
Execute l'action de réparer le bateau, avec le nombre de jetons passé en paramètres
*/
void Façade::executeRepairAction(int const tokens) {
	if (tokens > 0) {
		context->setAction(std::make_unique<RepairBoatAction>(tokens));
		int h = context->executeAction();
		boat->heal(h);
		recapText << "Reparer l'embarcation est une sage idee pour eviter de se retrouver au milieu"
			<< " de l'ocean accroche a une planche pour tenter de se maintenir a flot." << std::endl;
		recapText << std::endl << "Reparation : " << h << std::endl << std::endl;
	}
}

/*
Passe au jour suivant. Peut déclencher un évènement choisi de manière aléatoire, et 
consomme un certain nombre de poissons.
Ecrit également dans un fichier recap.txt le récapitulatif des actions et évènements.
*/
Status Façade::nextDay(std::map<TokensType, int>& tokens) {
	auto status = Status::onGoing;
	recapText.str(std::string());
	dayCount++;
	if (tokens[TokensType::fishingsTokens]) executeFishingAction(tokens[TokensType::fishingsTokens]);
	if (tokens[TokensType::rowingTokens]) executeRowingAction(tokens[TokensType::rowingTokens]);
	if (tokens[TokensType::healingTokens]) executeHealingAction(tokens[TokensType::healingTokens]);
	if (tokens[TokensType::repairTokens]) executeRepairAction(tokens[TokensType::repairTokens]);
	if (tokens[TokensType::upgradeFishingToken]) executeUpgradeFishingAction(tokens[TokensType::upgradeFishingToken]);
	if (tokens[TokensType::upgradeRowingToken]) executeUpgradeRowingAction(tokens[TokensType::upgradeRowingToken]);
	dailyEvent();
	fishCount.fetch_sub(fish_eating_number);
	std::cout << fishCount << std::endl;
	if (fishCount < 0) {
		player->takeDamage(fishCount * damage_starvation * -1);
		fishCount = 0;
	}
	if (distanceTravelled >= maxDistance)
		status = Status::victory;
	if (dayCount > maxDay) {
		status = Status::defeat;
	}
	if (player->getHp() <= 0 || boat->getHp() <= 0)
		status = Status::defeat;
	std::ofstream recap("resources/recap.txt", std::ios::trunc);
	recap << recapText.str() << std::endl;
	std::cout << recapText.str() << std::endl;
	recap.close();
	return status;
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

int Façade::getMaterials() {
	return materials;
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

void Façade::connectStormEventToFaçade(StormEvent* s) {
	s->damageBoatSignal.connect(boat.get(), &Entity::takeDamage);
	s->foodLostSignal.connect(this, &Façade::loseFood);
}

void Façade::connectWindEventToFaçade(WindEvent* w) {
	w->moveBackSignal.connect(this, &Façade::moveBack);
}

void Façade::moveBack(int const distance) {
	distanceTravelled > distance ?  distanceTravelled.fetch_sub(distance) : 0;
	recapText << "Un vent violent souffle pendant toute la journee, vous faisant perdre une partie de "
		<< "votre progression !" << std::endl;
	recapText << std::endl << "Distance parcourue : -" << distance << "km" << std::endl << std::endl;
}

void Façade::loseFood(int const food) {
	fishCount > food ? fishCount.fetch_sub(food) : 0;
	std::cout << fishCount << std::endl;
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

void Façade::executeUpgradeFishingAction(int const tokens) {
	if (tokens > 0 && materials >= rod_materials_required) {
		materials.fetch_sub(rod_materials_required);
		context->setAction(std::make_unique<UpgradeFishingAction>(tokens));
		fishingBonus += context->executeAction();
		recapText << "Avec les materiaux que vous avez recuperes, vous avez pu fabriquer une canne "
			<< " a peche. Cela vous permettra de recolter plus de poisson !" << std::endl;
		recapText << std::endl << "Canne a peche + 1" << std::endl << std::endl;
	}
}

void Façade::executeUpgradeRowingAction(int const tokens) {
	if (tokens > 0 && materials >= boat_materials_required) {
		materials.fetch_sub(boat_materials_required);
		context->setAction(std::make_unique<UpgradeRowingAction>(tokens));
		rowingBonus += context->executeAction();
		std::cout << rowingBonus << std::endl;
		recapText << "Avec les materiaux que vous avez recuperes, vous avez pu fabriquer de quoi mieux"
			<< " naviguer. Vous pourrez parcourir plus de distance avec votre barque !" << std::endl;
		recapText << std::endl << "Bateau ameliore" << std::endl << std::endl;
	}
}

bool Façade::getRowingUpgradeStatus() {
	return rowingBonus > 0;
}

bool Façade::getFishingUpgradeStatus() {
	return fishingBonus > 0;
}