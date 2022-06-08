#include "Action.h"

/**
Classe représentant l'action de pêcher.
*/
class FishingAction : public Action {
private:
	int baseFishRate = 1;
public:
	explicit FishingAction(int const tokenNb);
	int execute() override;
};

