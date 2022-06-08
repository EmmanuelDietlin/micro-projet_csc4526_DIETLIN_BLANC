#pragma once
#include "Boat.h"
#include "Player.h"
#include "Context.h"
#include <vector>
#include <map>
#include <sstream>
#include "signals.h"
#include "StormEvent.h"
#include "WindEvent.h"
#include "UpgradeFishingAction.h"
#include "UpgradeRowingAction.h"
#include <atomic>

const int max_tokens_nb = 5;
const int starting_fish_number = 2;
const int fish_eating_number = 2;
const int damage_starvation = 10;
const int proba_event = 100;
const int rod_materials_required = 20;
const int boat_materials_required = 40;

enum class TokensType { tokenNbr, fishingsTokens, rowingTokens, healingTokens, repairTokens, 
	upgradeFishingToken, upgradeRowingToken, remainingTokens };
enum class Status { onGoing, victory, defeat };

/**
Classe faisant l'interface vers le système de jeu. 
Fournit les méthodes permettant le déroulement du jeu jusqu'à la victoire ou la défaite du joueur.
*/
class Façade {
private:
	int action_tokens;
	std::atomic<int> fishCount;
	std::atomic<int> distanceTravelled = 0;
	int dayCount = 1;
	int maxDay;
	int maxDistance;
	std::atomic<int> materials;
	int fishingBonus = 0;
	int rowingBonus = 0;
	std::unique_ptr<Boat> boat;
	std::unique_ptr<Player> player;
	std::unique_ptr<Context> context;
	std::vector<std::shared_ptr<Event>> eventVector;
	std::stringstream recapText;
	void connectStormEventToFaçade(StormEvent* stormEvent);
	void connectWindEventToFaçade(WindEvent* windEvent);
	int random_n_to_m(int const nbMin, int const nbMax);
public:
	Façade(int const maxDay, int const MaxDistance, int const playerHp, 
		int const playerMaxHp, int const boatHp, int const boatMaxHp, int const materials);
	int getTokenNbr();
	int getDistanceTravelled();
	int getDayCount();
	int getFishCount();
	int getPlayerHp();
	int getBoatHp();
	int getMaterials();
	bool getRowingUpgradeStatus();
	bool getFishingUpgradeStatus();
	void executeRowingAction(int const tokens);
	void executeFishingAction(int const tokens);
	void executeHealingAction(int const tokens);
	void executeRepairAction(int const tokens);
	void executeUpgradeFishingAction(int const tokens);
	void executeUpgradeRowingAction(int const tokens);
	Status nextDay(std::map<TokensType, int>& tokens);
	void dailyEvent();
	void moveBack(int const distance);
	void loseFood(int const food);
	
};
