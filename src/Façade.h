#include "FishingAction.h"
#include "RowingAction.h"
#include "Boat.h"
#include "Player.h"
#include "Context.h"
#include "Data.h"
#include <vector>
#include <map>

const int max_tokens_nb = 5;
const int starting_fish_number = 2;
const int fish_eating_number = 2;
const int playerBaseHp = 100;
const int boatBaseHp = 200;

class Fa�ade {
private:
	int action_tokens;
	std::unique_ptr<Data> data;
	std::unique_ptr<Context> context;
public:
	Fa�ade();
	const int getTokenNbr();
	const int getDistanceTravelled();
	const int getDayCount();
	const int getFishCount();
	void executeRowingAction(int const tokens);
	void executeFishingAction(int const tokens);
	void nextDay();


};