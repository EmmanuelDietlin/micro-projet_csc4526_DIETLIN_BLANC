#include "GameplayFaçade.h"
#include "FishingAction.h"
#include "RowingAction.h"
#include "HealPlayerAction.h"
#include "RepairBoatAction.h"
#include "StormEvent.h"
#include "WindEvent.h"
#include "SeagullEvent.h"
#include <random>
#include <fstream>
#include <iostream>

/**
Constructeur de la classe Façade.
*
*@param maxDay  Nombre maximal de jours du jeu.
*@param MaxDistance Distance à parcourir.
*@param playerHp pv de départ du joueur.
*@param playerMaxHp pv max du joueur.
*@param boatHp pv de départ du bateau.
*@param boatMaxHp pv max du bateau.
*@param materials nombre de matériaux au démarrage.
*
*/
GameplayFaçade::GameplayFaçade(int const maxDay, int const maxDistance, int const playerHp, int const playerMaxHp,
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
	badEventVector.push_back(std::make_shared<StormEvent>());
	badEventVector.push_back(std::make_shared<WindEvent>());
	badEventVector.push_back(std::make_shared<SeagullEvent>());
	goodEventVector.push_back(std::make_shared<MaterialEvent>());
	connectStormEventToFaçade((StormEvent*)badEventVector[0].get());
	connectWindEventToFaçade((WindEvent*)badEventVector[1].get());
	connectSeagullEventToFaçade((SeagullEvent*)badEventVector[2].get());
	connectMaterialEventToFaçade((MaterialEvent*)goodEventVector[0].get());
}

/**
Renvoie le nombre de jetons du jeu.
* @return le nombre de jetons
*/
int GameplayFaçade::getTokenNbr() {
	return action_tokens;
}
/**
Renvoie le nombre de jours actuel du jeu.
* @return le nombre de jours
*/
int GameplayFaçade::getDayCount() {
	return dayCount;
}
/**
Renvoie la distance parcourue par le joueur.
* @return la distance parcourue
*/
int GameplayFaçade::getDistanceTravelled() {
	return distanceTravelled;
}

/**
Execute l'action de ramer, avec le nombre de jetons passé en paramètre
*@param tokens nombre de jetons pour l'action
*/
void GameplayFaçade::executeRowingAction(int const tokens) {
	context->setAction(std::make_unique<RowingAction>(tokens, &recapText, rowingBonus, boat.get()));
	distanceTravelled += context->executeAction();
}



/**
Execute l'action de pêcher, avec le nombre de jetons passé en paramètres
*@param tokens nombre de jetons pour l'action
*/
void GameplayFaçade::executeFishingAction(int const tokens) {
	context->setAction(std::make_unique<FishingAction>(tokens, &recapText, fishingBonus, player.get()));
	fishCount += context->executeAction();
}

/**
Execute l'action de se soigner, avec le nombre de jetons passé en paramètres
*@param tokens nombre de jetons pour l'action
*
*/
void GameplayFaçade::executeHealingAction(int const tokens) {
	context->setAction(std::make_unique<HealPlayerAction>(tokens, &recapText));
	player->heal(context->executeAction());
}

/**
Execute l'action de réparer le bateau, avec le nombre de jetons passé en paramètres
*@param tokens nombre de jetons pour l'action
*
*/
void GameplayFaçade::executeRepairAction(int const tokens) {
	context->setAction(std::make_unique<RepairBoatAction>(tokens, &recapText));
	boat->heal(context->executeAction());
}

/**
Passe au jour suivant. Peut déclencher un évènement choisi de manière aléatoire, et consomme un certain nombre de poissons.
Ecrit également dans un fichier recap.txt le récapitulatif des actions et évènements.
*@param tokens map contenant tous les jetons d'actions
*@return le status du jeu (onGoing, victory, defeat)
*/
Status GameplayFaçade::nextDay(std::map<TokensType, int>& tokens) {
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
	fishCount -= (fish_eating_number);
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
	recap.close();
	return status;
}

/**
Renvoie le nombre de poissons actuellement en possession du joueur.
* @return le nombre de poissons
*/
int GameplayFaçade::getFishCount() {
	return fishCount;
}
/**
Renvoie la vie actuelle du joueur.
* @return les points de vie
*/
int GameplayFaçade::getPlayerHp() {
	return player->getHp();
}
/**
Renvoie la vie actuelle du bateau.
* @return les points de vie
*/
int GameplayFaçade::getBoatHp() {
	return boat->getHp();
}
/**
Renvoie le nombre de matériaux en possession du joueur.
* @return le nombre de matériaux
*/
int GameplayFaçade::getMaterials() {
	return materials;
}

/**
Méthode exécutant ou non un évènement choisit au hasard selon un tirage aléatoire.
*/
void GameplayFaçade::dailyEvent() {
	int probaGoodDailyEvent = random_n_to_m(1, 100);
	int probaBadDailyEvent = random_n_to_m(1, 100);
	if (probaGoodDailyEvent <= proba_good_event) {
		size_t size = goodEventVector.size();
		context->setEvent(goodEventVector[random_n_to_m(0, size - 1)]);
		context->executeEvent();
	}
	if (probaBadDailyEvent <= proba_bad_event) {
		size_t size = badEventVector.size();
		context->setEvent(badEventVector[random_n_to_m(0, size - 1)]);
		context->executeEvent();
	}
}

/**
* Connecte un évènement de type StormEvent à la méthode loseFood de la façade et takeDamage du bateau.
*/
void GameplayFaçade::connectStormEventToFaçade(StormEvent* s) {
	s->stormEventSignal.connect(this, &GameplayFaçade::writeStormEvent);
	s->damageBoatSignal.connect(this, &GameplayFaçade::damageBoat);
	s->foodLostSignal.connect(this, &GameplayFaçade::loseFood);
}

/**
* Connecte un évènement de type WindEvent à la méthode moveBack de la façade.
*/
void GameplayFaçade::connectWindEventToFaçade(WindEvent* w) {
	w->windEventSignal.connect(this, &GameplayFaçade::writeWindEvent);
	w->moveBackSignal.connect(this, &GameplayFaçade::moveBack);
}

/**
* Connecte un évènement de type SeagullEvent à la méthode loseFood de la façade et takeDamage du player.
*/
void GameplayFaçade::connectSeagullEventToFaçade(SeagullEvent* s) {
	s->seagullEventSignal.connect(this, &GameplayFaçade::writeSeagullEvent);
	s->damagePlayerSignal.connect(this, &GameplayFaçade::damagePlayer);
	s->foodLostSignal.connect(this, &GameplayFaçade::loseFood);
}

/**
* Connecte un évènement de type MaterialEvent à la méthode findMaterial de la façade.
*/
void GameplayFaçade::connectMaterialEventToFaçade(MaterialEvent* m) {
	m->materialEventSignal.connect(this, &GameplayFaçade::writeMaterialEvent);
	m->materialFoundSignal.connect(this, &GameplayFaçade::findMaterial);
}

/**
* Diminue la distance parcourue. Ne peut pas faire passer la distance parcourue en dessous de 0.
* @param distance distance à retrancher
*/
void GameplayFaçade::moveBack(int const distance) {
	distanceTravelled = std::max(distanceTravelled - distance, 0);
	recapText << std::endl << "Distance parcourue : -" << distance << "km" << std::endl;
}

/**
* Diminue la quantité de nourriture. Ne peut pas faire passer la quantité de poisson en dessous de 0.
* @param food nombre de poissons à retrancher
*/
void GameplayFaçade::loseFood(int const food) {
	fishCount -= std::max(fishCount - food, 0);
	recapText << std::endl << "Poissons : -" << food << std::endl;
}

/**
* Augmente la quantité de matériaux.
* @param material nombre de matériaux à ajouter
*/
void GameplayFaçade::findMaterial(int const material) {
	materials += (material);
	recapText << std::endl << "Materiaux : +" << material << std::endl;
}

/**
* Ecrit le message annonçant un événement de type StormEvent.
*/
void GameplayFaçade::writeStormEvent() {
	recapText << "La tempete fait bringuebaler votre embarcation dans tous les sens,"
		<< " une partie de vos provisions tombe par dessus bord et votre bateau est abime !" << std::endl;
}

/**
* Ecrit le message annonçant un événement de type WindEvent.
*/
void GameplayFaçade::writeWindEvent() {
	recapText << "Un vent violent souffle pendant toute la journee, vous faisant perdre une partie de "
		<< "votre progression !" << std::endl;
}

/**
* Ecrit le message annonçant un événement de type SeagullEvent.
*/
void GameplayFaçade::writeSeagullEvent() {
	recapText << "Vous vous faites attaquer par un groupe de mouettes,"
		<< " une partie de vos provisions est perdue et vous etes blesse !" << std::endl;
}

/**
* Ecrit le message annonçant un événement de type MaterialEvent.
*/
void GameplayFaçade::writeMaterialEvent() {
	recapText << "Aujourd'hui est un jour de chance,"
		<< " vous trouvez des materiaux pour vos ameliorations !" << std::endl;
}

int GameplayFaçade::random_n_to_m(int const nbMin, int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(nbMin, nbMax);
	return distribution(engine);
}


/**
* Execute l'action d'améliorer la pêche.
* @param tokens nombre de jetons pour l'amélioration
*/
void GameplayFaçade::executeUpgradeFishingAction(int const tokens) {
	context->setAction(std::make_unique<UpgradeFishingAction>(tokens, &recapText, materials, rod_materials_required));
	int upgradeResult = context->executeAction();
	if (upgradeResult > 0) {
		fishingBonus += upgradeResult;
		materials -= rod_materials_required;
	}
}
/**
* Execute l'action d'améliorer le bateau.
* @param tokens nombre de jetons pour l'amélioration
*/
void GameplayFaçade::executeUpgradeRowingAction(int const tokens) {
	context->setAction(std::make_unique<UpgradeRowingAction>(tokens, &recapText, materials, boat_materials_required));
	int upgradeResult = context->executeAction();
	if (upgradeResult > 0) {
		rowingBonus += upgradeResult;
		materials -= boat_materials_required;
	}
}


/**
* Renvoie si l'on peut améliorer le bateau ou non.
* @return vrai si on peut améliorer
*/
bool GameplayFaçade::getRowingUpgradeStatus() {
	return rowingBonus > 0;
}


/**
* Renvoie si l'on peut améliorer la pêche ou non.
* @return vrai si on peut améliorer
*/
bool GameplayFaçade::getFishingUpgradeStatus() {
	return fishingBonus > 0;
}

/**
* Fonction pour tester la bonne execution de StormEvent
*/
void GameplayFaçade::executeStormEvent() {
	context->setEvent(badEventVector[0]);
	context->executeEvent();
}

/**
* Fonction pour tester la bonne execution de WindEvent
*/
void GameplayFaçade::executeWindEvent() {
	context->setEvent(badEventVector[1]);
	context->executeEvent();
}

/**
* Fonction pour tester la bonne execution de SeagullEvent
*/
void GameplayFaçade::executeSeagullEvent() {
	context->setEvent(badEventVector[2]);
	context->executeEvent();
}
/**
* Fonction pour tester la bonne execution de MaterialEvent
*/
void GameplayFaçade::executeMaterialEvent() {
	context->setEvent(goodEventVector[0]);
	context->executeEvent();
}

/// <summary>
/// Occasionne des dommages au bateau et écrit l'action dans le récapitulatif
/// </summary>
/// <param name="dmg"> quantite de dommages à infliger </param>
void GameplayFaçade::damageBoat(int const dmg) {
	boat->takeDamage(dmg);
	recapText << std::endl << "Pv bateau -" << dmg << std::endl << std::endl;
}


/// <summary>
/// Occasionne des dommages au joueur et écrit l'action dans le récapitulatif
/// </summary>
/// <param name="dmg"> quantite de dommages à infliger </param>
void GameplayFaçade::damagePlayer(int const dmg) {
	player->takeDamage(dmg);
	recapText << std::endl << "Pv -" << dmg << std::endl << std::endl;
}

