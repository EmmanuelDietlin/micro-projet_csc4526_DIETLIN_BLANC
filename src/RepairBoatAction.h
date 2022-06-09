#include "Action.h"

/**
Classe repr�sentant l'action de r�parer le bateau
*/
class RepairBoatAction : public Action {
private:
	int const repairFactor = 15;
public:
	explicit RepairBoatAction(int const tokenNb);
	int execute() override;
};