#include "Action.h"
#include "Player.h"

/**
Classe représentant l'action de pêcher.
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

