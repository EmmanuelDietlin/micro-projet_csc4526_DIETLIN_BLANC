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

class Façade {
private:
	int action_tokens;
	std::unique_ptr<Boat> boat;
	std::unique_ptr<Player> player;
	std::unique_ptr<Event> evnt;
	std::unique_ptr<Data> data;
	std::map<std::string, std::unique_ptr<Action>> actions;
public:
	Façade();
	const int getTokenNbr();
	const int getDistanceTravelled();
	const int getDayCount();
	const int getFishCount();
	void executeRowingAction(int const tokens);
	void executeFishingAction(int const tokens);
	void nextDay();


};