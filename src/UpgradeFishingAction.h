#include "Action.h"

class UpgradeFishingAction : public Action {
public:
	explicit UpgradeFishingAction(int const tokenNb);
	int execute() override;
private:
	int const upgradeFactor = 1;
};