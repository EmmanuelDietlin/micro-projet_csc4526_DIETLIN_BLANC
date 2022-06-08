#include "Action.h"

/**
Classe représentant l'action de se soigner
*/
class HealPlayerAction : public Action {
private:
	int const healFactor = 20;
public:
	explicit HealPlayerAction(int const tokenNb);
	int execute() override;
};