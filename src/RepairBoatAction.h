#include "Action.h"

/**
Classe représentant l'action de réparer le bateau
*/
class RepairBoatAction : public Action {
private:
	int const repairFactor = 20;
public:
	explicit RepairBoatAction(int const tokenNb);
	int execute() override;
};