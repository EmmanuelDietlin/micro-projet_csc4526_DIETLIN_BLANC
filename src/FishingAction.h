#include "Action.h"
#include "Player.h"

/**
Classe repr�sentant l'action de p�cher.
*/
class FishingAction : public Action {
private:
	int baseFishRate = 1;
	int fishingBonus;
	Player* player;
public:
	explicit FishingAction(int const tokenNb, std::stringstream* recapText, int const fishingBonus, Player* player);
	int execute() override;
};

