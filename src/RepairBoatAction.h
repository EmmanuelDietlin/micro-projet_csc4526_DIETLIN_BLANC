#include "Action.h"

class RepairBoatAction : public Action {
private:
	int const repairFactor = 20;
public:
	explicit RepairBoatAction(int const tokenNb);
	int execute() override;
};