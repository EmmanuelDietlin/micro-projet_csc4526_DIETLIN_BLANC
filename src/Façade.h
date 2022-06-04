#pragma once
#include "Boat.h"
#include "Player.h"
#include "Context.h"
#include <vector>
#include <map>
#include "signals.h"
#include "myMain.h"
#include "StormEvent.h"
#include "WindEvent.h"

const int max_tokens_nb = 5;
const int starting_fish_number = 2;
const int fish_eating_number = 2;
const int damage_starvation = 10;
const int proba_event = 100;

class Façade {
private:
	int action_tokens;
	int fishCount;
	int distanceTravelled = 0;
	int dayCount = 1;
	int maxDay;
	int maxDistance;
	std::unique_ptr<Boat> boat;
	std::unique_ptr<Player> player;
	std::unique_ptr<Context> context;
	ImGuiWindow* imguiWindow;
	std::vector<std::unique_ptr<Event>> eventVector;
public:
	Façade(int const maxDay, int const MaxDistance, int const playerHp, 
		int const playerMaxHp, int const boatHp, int const boatMaxHp, ImGuiWindow* imguiWindow);
	int getTokenNbr();
	int getDistanceTravelled();
	int getDayCount();
	int getFishCount();
	int getPlayerHp();
	int getBoatHp();
	void executeRowingAction(int const tokens);
	void executeFishingAction(int const tokens);
	void executeHealingAction(int const tokens);
	void executeRepairAction(int const tokens);
	void nextDay(std::map<TokensType, int>& tokens);
	void newGame();
	void deathPlayer();
	void connectDeathPlayerToFaçade(Player* player);
	void deathBoat();
	void connectDeathBoatToFaçade(Boat* boat);
	void defeat();
	void victory();
	void dailyEvent();
	void connectStormEventToFaçade(StormEvent* stormEvent);
	void connectWindEventToFaçade(WindEvent* windEvent);
	void moveBack(int const distance);
	void loseFood(int const food);
	int random_n_to_m(int const nbMin, int const nbMax);
};