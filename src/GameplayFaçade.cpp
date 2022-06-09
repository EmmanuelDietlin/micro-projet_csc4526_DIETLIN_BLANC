#include "GameplayFa�ade.h"
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
GameplayFa�ade::GameplayFa�ade(int const maxDay, int const maxDistance, int const playerHp, int const playerMaxHp,
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
	eventVector.push_back(std::make_shared<SeagullEvent>());	
	eventVector.push_back(std::make_shared<MaterialEvent>());	
	connectStormEventToFa�ade((StormEvent*)eventVector[0].get());
	connectWindEventToFa�ade((WindEvent*)eventVector[1].get());
	connectSeagullEventToFa�ade((SeagullEvent*)eventVector[2].get());
	connectMaterialEventToFa�ade((MaterialEvent*)eventVector[3].get());
}

/**
Renvoie le nombre de jetons du jeu.
* @return le nombre de jetons
*/
int GameplayFa�ade::getTokenNbr() {
	return action_tokens;
}
/**
Renvoie le nombre de jours actuel du jeu.
* @return le nombre de jours
*/
int GameplayFa�ade::getDayCount() {
	return dayCount;
}
/**
Renvoie la distance parcourue par le joueur.
* @return la distance parcourue
*/
int GameplayFa�ade::getDistanceTravelled() {
	return distanceTravelled;
}

/**
Execute l'action de ramer, avec le nombre de jetons pass� en param�tre
*@param tokens nombre de jetons pour l'action
*/
void GameplayFa�ade::executeRowingAction(int const tokens) {
	int d = rowingBonus;
	int toks = tokens;
	if (boat->stronglyDamaged()) {
		toks--;
		recapText << "L'etat du bateau rend difficile la naviguation !"
			<< std::endl << "Distance parcourue reduite" << std::endl << std::endl;
	}
	if (toks > 0) {
		context->setAction(std::make_unique<RowingAction>(toks));
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
void GameplayFa�ade::executeFishingAction(int const tokens) {
	int f = fishingBonus;
	int toks = tokens;
	if (player->stronglyDamaged()) {
		toks--;
		recapText << "Du fait de votre etat, vous ne pouvez pas agir autant que vous le souhaitez !"
			<< std::endl << "Nombre de poissons peche diminue" << std::endl << std::endl;
	}
	if (toks > 0) {
		context->setAction(std::make_unique<FishingAction>(toks));
		f += context->executeAction();
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
void GameplayFa�ade::executeHealingAction(int const tokens) {
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
void GameplayFa�ade::executeRepairAction(int const tokens) {
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
Status GameplayFa�ade::nextDay(std::map<TokensType, int>& tokens) {
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
int GameplayFa�ade::getFishCount() {
	return fishCount;
}
/**
Renvoie la vie actuelle du joueur.
* @return les points de vie
*/
int GameplayFa�ade::getPlayerHp() {
	return player->getHp();
}
/**
Renvoie la vie actuelle du bateau.
* @return les points de vie
*/
int GameplayFa�ade::getBoatHp() {
	return boat->getHp();
}
/**
Renvoie le nombre de mat�riaux en possession du joueur.
* @return le nombre de mat�riaux
*/
int GameplayFa�ade::getMaterials() {
	return materials;
}

/**
M�thode ex�cutant ou non un �v�nement choisit au hasard selon un tirage al�atoire.
*/
void GameplayFa�ade::dailyEvent() {
	int probaDailyEvent = random_n_to_m(1, 100);
	if (probaDailyEvent <= proba_event) {
		size_t size = eventVector.size();
		context->setEvent(eventVector[random_n_to_m(0, size - 1)]);
		context->executeEvent();
	}
}

/**
* Connecte un �v�nement de type StormEvent � la m�thode loseFood de la fa�ade et takeDamage du bateau.
*/
void GameplayFa�ade::connectStormEventToFa�ade(StormEvent* s) {
	s->stormEventSignal.connect(this, &GameplayFa�ade::writeStormEvent);
	s->damageBoatSignal.connect(this, &GameplayFa�ade::damageBoat);
	s->foodLostSignal.connect(this, &GameplayFa�ade::loseFood);
}

/**
* Connecte un �v�nement de type WindEvent � la m�thode moveBack de la fa�ade.
*/
void GameplayFa�ade::connectWindEventToFa�ade(WindEvent* w) {
	w->windEventSignal.connect(this, &GameplayFa�ade::writeWindEvent);
	w->moveBackSignal.connect(this, &GameplayFa�ade::moveBack);
}

/**
* Connecte un �v�nement de type SeagullEvent � la m�thode loseFood de la fa�ade et takeDamage du player.
*/
void GameplayFa�ade::connectSeagullEventToFa�ade(SeagullEvent* s) {
	s->seagullEventSignal.connect(this, &GameplayFa�ade::writeSeagullEvent);
	s->damagePlayerSignal.connect(this, &GameplayFa�ade::damagePlayer);
	s->foodLostSignal.connect(this, &GameplayFa�ade::loseFood);
}

/**
* Connecte un �v�nement de type MaterialEvent � la m�thode findMaterial de la fa�ade.
*/
void GameplayFa�ade::connectMaterialEventToFa�ade(MaterialEvent* m) {
	m->materialEventSignal.connect(this, &GameplayFa�ade::writeMaterialEvent);
	m->materialFoundSignal.connect(this, &GameplayFa�ade::findMaterial);
}

/**
* Diminue la distance parcourue. Ne peut pas faire passer la distance parcourue en dessous de 0.
* @param distance distance � retrancher
*/
void GameplayFa�ade::moveBack(int const distance) {
	distanceTravelled.fetch_sub(distance);
	if (distanceTravelled.load() < 0) {
		distanceTravelled.store(0);
	}
	recapText << std::endl << "Distance parcourue : -" << distance << "km" << std::endl;
}

/**
* Diminue la quantit� de nourriture. Ne peut pas faire passer la quantit� de poisson en dessous de 0.
* @param food nombre de poissons � retrancher
*/
void GameplayFa�ade::loseFood(int const food) {
	fishCount.fetch_sub(food);
	if (fishCount.load() < 0) {
		fishCount.store(0);
	}
	recapText << std::endl << "Poissons : -" << food << std::endl;
}

/**
* Augmente la quantit� de mat�riaux.
* @param material nombre de mat�riaux � ajouter
*/
void GameplayFa�ade::findMaterial(int const material) {
	materials.fetch_add(material);
	recapText << std::endl << "Materiaux : +" << material << std::endl;
}

/**
* Ecrit le message annon�ant un �v�nement de type StormEvent.
*/
void GameplayFa�ade::writeStormEvent() {
	recapText << "La tempete fait bringuebaler votre embarcation dans tous les sens,"
		<< " une partie de vos provisions tombe par dessus bord et votre bateau est abime !" << std::endl;
}

/**
* Ecrit le message annon�ant un �v�nement de type WindEvent.
*/
void GameplayFa�ade::writeWindEvent() {
	recapText << "Un vent violent souffle pendant toute la journee, vous faisant perdre une partie de "
		<< "votre progression !" << std::endl;
}

/**
* Ecrit le message annon�ant un �v�nement de type SeagullEvent.
*/
void GameplayFa�ade::writeSeagullEvent() {
	recapText << "Vous vous faites attaquer par un groupe de mouettes,"
		<< " une partie de vos provisions est perdue et vous etes blesse !" << std::endl;
}

/**
* Ecrit le message annon�ant un �v�nement de type MaterialEvent.
*/
void GameplayFa�ade::writeMaterialEvent() {
	recapText << "Aujourd'hui est un jour de chance,"
		<< " vous trouvez des materiaux pour vos ameliorations !" << std::endl;
}

int GameplayFa�ade::random_n_to_m(int const nbMin, int const nbMax)
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
void GameplayFa�ade::executeUpgradeFishingAction(int const tokens) {
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
void GameplayFa�ade::executeUpgradeRowingAction(int const tokens) {
	int tkns = tokens;
	if (tkns > 0 && materials >= boat_materials_required) {
		if (tkns > 1) tkns = 1;
		materials.fetch_sub(boat_materials_required);
		context->setAction(std::make_unique<UpgradeRowingAction>(tokens));
		rowingBonus += context->executeAction();
		recapText << "Avec les materiaux que vous avez recuperes, vous avez pu fabriquer de quoi mieux"
			<< " naviguer. Vous pourrez parcourir plus de distance avec votre barque !" << std::endl;
		recapText << std::endl << "Bateau ameliore" << std::endl << std::endl;
	}
}


/**
* Renvoie si l'on peut am�liorer le bateau ou non.
* @return vrai si on peut am�liorer
*/
bool GameplayFa�ade::getRowingUpgradeStatus() {
	return rowingBonus > 0;
}


/**
* Renvoie si l'on peut am�liorer la p�che ou non.
* @return vrai si on peut am�liorer
*/
bool GameplayFa�ade::getFishingUpgradeStatus() {
	return fishingBonus > 0;
}

/**
* Fonction pour tester la bonne execution de StormEvent
*/
void GameplayFa�ade::executeStormEvent() {
	context->setEvent(eventVector[0]);
	context->executeEvent();
}

/**
* Fonction pour tester la bonne execution de WindEvent
*/
void GameplayFa�ade::executeWindEvent() {
	context->setEvent(eventVector[1]);
	context->executeEvent();
}

/**
* Fonction pour tester la bonne execution de SeagullEvent
*/
void GameplayFa�ade::executeSeagullEvent() {
	context->setEvent(eventVector[2]);
	context->executeEvent();
}
/**
* Fonction pour tester la bonne execution de MaterialEvent
*/
void GameplayFa�ade::executeMaterialEvent() {
	context->setEvent(eventVector[3]);
	context->executeEvent();
}

/// <summary>
/// Occasionne des dommages au bateau et �crit l'action dans le r�capitulatif
/// </summary>
/// <param name="dmg"> quantite de dommages � infliger </param>
void GameplayFa�ade::damageBoat(int const dmg) {
	boat->takeDamage(dmg);
	recapText << std::endl << "Pv bateau -" << dmg << std::endl << std::endl;
}


/// <summary>
/// Occasionne des dommages au joueur et �crit l'action dans le r�capitulatif
/// </summary>
/// <param name="dmg"> quantite de dommages � infliger </param>
void GameplayFa�ade::damagePlayer(int const dmg) {
	player->takeDamage(dmg);
	recapText << std::endl << "Pv -" << dmg << std::endl << std::endl;
}

