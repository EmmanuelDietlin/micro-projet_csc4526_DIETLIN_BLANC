#include "Action.h"

class FishingAction : public Action {
private:
	int baseFishRate = 1;
public:
	int execute() override;
};

