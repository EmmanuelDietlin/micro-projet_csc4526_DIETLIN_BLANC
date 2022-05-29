#include "Action.h"

class FishingAction : public Action {
private:
	int baseFishRate = 1;
public:
	explicit FishingAction(int const tokenNb);
	int execute() override;
};

