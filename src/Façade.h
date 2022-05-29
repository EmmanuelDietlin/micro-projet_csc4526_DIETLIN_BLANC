#include "FishingAction.h"
#include "RowingAction.h"
#include "Boat.h"
#include "Player.h"
#include "Context.h"
#include "Data.h"
#include <vector>
#include <map>

const int max_tokens_nb = 5;

class Façade {
private:
	int action_tokens;
	std::unique_ptr<Boat> boat;
	std::unique_ptr<Player> player;
	std::unique_ptr<Event> evnt;
	std::map<std::string, std::unique_ptr<Action>> actions;
public:
	Façade();
	//Définir les méthodes de la façade
	int addTokenToFishing();
	int addTokenToRowing();
	int removeTokenToFishing();
	int removeTokenToRowing();
	const int getTokenNbr();


};