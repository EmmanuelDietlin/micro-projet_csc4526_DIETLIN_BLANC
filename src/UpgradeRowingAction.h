#include "Action.h"

class UpgradeRowingAction : public Action {
public:
	explicit UpgradeRowingAction(int const tokenNb);
	int execute() override;
private:
	int const upgradeFactor = 50;
};