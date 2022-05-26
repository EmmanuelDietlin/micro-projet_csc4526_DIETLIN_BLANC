#include "Boat.h"
#include "Player.h"
#include "Context.h"
#include "Data.h"

class Façade {
private:
	int action_tokens;
	std::unique_ptr<Boat> boat;
	std::unique_ptr<Player> player;
public:
	//Définir les méthodes de la façade

};