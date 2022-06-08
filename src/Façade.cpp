#include "Fa�ade.h"
#include "FishingAction.h"
#include "RowingAction.h"
#include "HealPlayerAction.h"
#include "RepairBoatAction.h"
#include "StormEvent.h"
#include "WindEvent.h"
#include <random>
#include <fstream>
#include <iostream>

/**
Constructeur de la classe Fa�ade.
*
*@param maxDay  Nombre maximal de jours du jeu.
*@param MaxDistance Distance � parcourir.
*@param playerHp pv de d�part du joueur.
*@param playerMaxHp pv max du joueur.
*@param boatHp pv de d�part du bateau.
*@param boatMaxHp pv max du bateau.
*@param materials nombre de mat�riaux au d�marrage.
*
*/
Fa�ade::Fa�ade(int const maxDay, int const maxDistance, int const playerHp, int const playerMaxHp,
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
	connectStormEventToFa�ade((StormEvent*)eventVector[0].get());
	connectWindEventToFa�ade((WindEvent*)eventVector[1].get()); 
}

/**
Renvoie le nombre de jetons du jeu.
* @return le nombre de jetons
*/
int Fa�ade::getTokenNbr() {
	return action_tokens;
}
/**
Renvoie le nombre de jours actuel du jeu.
* @return le nombre de jours
*/
int Fa�ade::getDayCount() {
	return dayCount;
}
/**
Renvoie la distance parcourue par le joueur.
* @return la distance parcourue
*/
int Fa�ade::getDistanceTravelled() {
	return distanceTravelled;
}

/**
Execute l'action de ramer, avec le nombre de jetons pass� en param�tre
*@param tokens nombre de jetons pour l'action
*/
void Fa�ade::executeRowingAction(int const tokens) {
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

/**
Execute l'action de p�cher, avec le nombre de jetons pass� en param�tres
*@param tokens nombre de jetons pour l'action
*/
void Fa�ade::executeFishingAction(int const tokens) {
	int f = fishingBonus;
	if (tokens > 0) {
		context->setAction(std::make_unique<FishingAction>(tokens));
		f = context->executeAction();
	}
	fishCount.fetch_add(f);
	//if (f > 0) {
		if (f < 3) {
			recapText << "Vous avez lance votre ligne dans l'eau, mais la chance ne vous a pas sourit : seuls quelques malheureux"
				<< " poissons ont mordu a l'appat. Il va sans doute falloir vous rationner..." << std::endl;
		}
		else {
			recapText << "La chance vous a sourit : vous n'avez eu qu'a lancer votre ligne dans l'eau, et aussitot de nombreux"
				<< " poissons se sont jetes dessus ! Sacre festin en perspective !" << std::endl;
		}
		recapText << std::endl << "Poissons peches : " << f << std::endl << std::endl;
	//}
	
}

/**
Execute l'action de se soigner, avec le nombre de jetons pass� en param�tres
*@param tokens nombre de jetons pour l'action
*
*/
void Fa�ade::executeHealingAction(int const tokens) {
	if (tokens > 0) {
		context->setAction(std::make_unique<HealPlayerAction>(tokens));
		int h = context->executeAction();
		player->heal(h);
		recapText << "Un peu de repos ne fait pas de mal ! En vous reposant, vous avez pu recuperer"
			<< " une partie de votre energie" << std::endl;
		recapText << std::endl << "Vie : +" << h << std::endl << std::endl;
	}
}

/**
Execute l'action de r�parer le bateau, avec le nombre de jetons pass� en param�tres
*@param tokens nombre de jetons pour l'action
*
*/
void Fa�ade::executeRepairAction(int const tokens) {
	if (tokens > 0) {
		context->setAction(std::make_unique<RepairBoatAction>(tokens));
		int h = context->executeAction();
		boat->heal(h);
		recapText << "Reparer l'embarcation est une sage idee pour eviter de se retrouver au milieu"
			<< " de l'ocean accroche a une planche pour tenter de se maintenir a flot." << std::endl;
		recapText << std::endl << "Reparation : " << h << std::endl << std::endl;
	}
}

/**
Passe au jour suivant. Peut d�clencher un �v�nement choisi de mani�re al�atoire, et consomme un certain nombre de poissons.
Ecrit �galement dans un fichier recap.txt le r�capitulatif des actions et �v�nements.
*@param tokens map contenant tous les jetons d'actions
*@return le status du jeu (onGoing, victory, defeat)
*/
Status Fa�ade::nextDay(std::map<TokensType, int>& tokens) {
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
		recapText << "Le manque de nourriture vous affaiblit !" << std::endl <<
			"pv " << fishCount * damage_starvation << std::endl << std::endl;
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

/**
Renvoie le nombre de poissons actuellement en possession du joueur.
* @return le nombre de poissons
*/
int Fa�ade::getFishCount() {
	return fishCount;
}
/**
Renvoie la vie actuelle du joueur.
* @return les points de vie
*/
int Fa�ade::getPlayerHp() {
	return player->getHp();
}
/**
Renvoie la vie actuelle du bateau.
* @return les points de vie
*/
int Fa�ade::getBoatHp() {
	return boat->getHp();
}
/**
Renvoie le nombre de mat�riaux en possession du joueur.
* @return le nombre de mat�riaux
*/
int Fa�ade::getMaterials() {
	return materials;
}

/**
M�thode ex�cutant ou non un �v�nement choisit au hasard selon un tirage al�atoire.
*/
void Fa�ade::dailyEvent() {
	int probaDailyEvent = random_n_to_m(1, 100);
	std::cout << probaDailyEvent << std::endl;
	if (probaDailyEvent <= proba_event) {
		size_t size = eventVector.size();
		context->setEvent(eventVector[random_n_to_m(0, size - 1)]);
		context->executeEvent();
	}
}


/**
Connecte un �v�nement de type StormEvent � la m�thode takeDamage de la fa�ade.
*/
void Fa�ade::connectStormEventToFa�ade(StormEvent* s) {
	s->damageBoatSignal.connect(boat.get(), &Entity::takeDamage);
	s->foodLostSignal.connect(this, &Fa�ade::loseFood);
}

/**
* Connecte un �v�nement de type WindEvent � la m�thode moveBack de la fa�ade.
*/
void Fa�ade::connectWindEventToFa�ade(WindEvent* w) {
	w->moveBackSignal.connect(this, &Fa�ade::moveBack);
}

/**
* Diminue la distance parcourue. Ne peut pas faire passer la distance parcourue en dessous de 0.
* @param distance distance � retrancher
*/
void Fa�ade::moveBack(int const distance) {
	distanceTravelled > distance ?  distanceTravelled.fetch_sub(distance) : 0;
	recapText << "Un vent violent souffle pendant toute la journee, vous faisant perdre une partie de "
		<< "votre progression !" << std::endl;
	recapText << std::endl << "Distance parcourue : -" << distance << "km" << std::endl << std::endl;
}

/**
* Diminue la quantit� de nourriture. Ne peut pas faire passer la quantit� de poisson en dessous de 0.
* @param food nombre de poissons � retrancher
*/
void Fa�ade::loseFood(int const food) {
	fishCount > food ? fishCount.fetch_sub(food) : 0;
	std::cout << fishCount << std::endl;
	recapText << "La tempete fait bringuebaler votre embarcation dans tous les sens, et "
		<< " une partie de vos provisions tombe par dessus bord !" << std::endl;
	recapText << std::endl << "Poissons : -" << food << std::endl << std::endl;
}

int Fa�ade::random_n_to_m(int const nbMin, int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(nbMin, nbMax);
	return distribution(engine);
}


/**
* Execute l'action d'am�liorer la p�che.
* @param tokens nombre de jetons pour l'am�lioration
*/
void Fa�ade::executeUpgradeFishingAction(int const tokens) {
	int tkns = tokens;
	if (tkns > 0 && materials >= rod_materials_required) {
		if (tkns > 1) tkns = 1;
		materials.fetch_sub(rod_materials_required);
		context->setAction(std::make_unique<UpgradeFishingAction>(tokens));
		fishingBonus += context->executeAction();
		recapText << "Avec les materiaux que vous avez recuperes, vous avez pu fabriquer une canne "
			<< " a peche. Cela vous permettra de recolter plus de poisson !" << std::endl;
		recapText << std::endl << "Canne a peche + 1" << std::endl << std::endl;
	}
}
/**
* Execute l'action d'am�liorer le bateau.
* @param tokens nombre de jetons pour l'am�lioration
*/
void Fa�ade::executeUpgradeRowingAction(int const tokens) {
	int tkns = tokens;
	if (tkns > 0 && materials >= boat_materials_required) {
		if (tkns > 1) tkns = 1;
		materials.fetch_sub(boat_materials_required);
		context->setAction(std::make_unique<UpgradeRowingAction>(tokens));
		rowingBonus += context->executeAction();
		std::cout << rowingBonus << std::endl;
		recapText << "Avec les materiaux que vous avez recuperes, vous avez pu fabriquer de quoi mieux"
			<< " naviguer. Vous pourrez parcourir plus de distance avec votre barque !" << std::endl;
		recapText << std::endl << "Bateau ameliore" << std::endl << std::endl;
	}
}


/**
* Renvoie si l'on peut am�liorer le bateau ou non.
* @return vrai si on peut am�liorer
*/
bool Fa�ade::getRowingUpgradeStatus() {
	return rowingBonus > 0;
}


/**
* Renvoie si l'on peut am�liorer la p�che ou non.
* @return vrai si on peut am�liorer
*/
bool Fa�ade::getFishingUpgradeStatus() {
	return fishingBonus > 0;
}