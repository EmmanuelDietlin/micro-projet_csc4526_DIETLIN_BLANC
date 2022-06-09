#include "Action.h"

/**
Classe représentant l'action de se soigner
*/
class HealPlayerAction : public Action {
private:
	int const healFactor = 15;
public:
	explicit HealPlayerAction(int const tokenNb);
	int execute() override;
};