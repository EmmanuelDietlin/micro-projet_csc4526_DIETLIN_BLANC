#include "Action.h"

/**
Classe représentant l'action de réparer le bateau
*/
class RepairBoatAction : public Action {
private:
	int const repairFactor = 15;
public:
	explicit RepairBoatAction(int const tokenNb);
	int execute() override;
};