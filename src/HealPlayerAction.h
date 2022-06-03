#include "Action.h"

class HealPlayerAction : public Action {
private:
	int const healFactor = 20;
public:
	explicit HealPlayerAction(int const tokenNb);
	int execute() override;
};