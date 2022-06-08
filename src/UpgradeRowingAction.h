#include "Action.h"

/**
Classe repr�sentant l'action d'am�liorer la naviguation
*/
class UpgradeRowingAction : public Action {
public:
	explicit UpgradeRowingAction(int const tokenNb);
	int execute() override;
private:
	int const upgradeFactor = 50;
};