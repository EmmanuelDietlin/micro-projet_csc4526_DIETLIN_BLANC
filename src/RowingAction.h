#include "Action.h"
#include "Boat.h"

/**
Classe représentant l'action de ramer/naviguer
*/
class RowingAction : public Action {
private:
	int baseDistance = 100;
	int rowingBonus;
	Boat* boat;
public:
	explicit RowingAction(int const tokenNb, std::stringstream* recapText, int const rowingBonus, Boat* boat);
	int execute() override;
};