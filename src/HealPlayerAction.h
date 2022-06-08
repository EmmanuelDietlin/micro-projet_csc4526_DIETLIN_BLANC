#include "Action.h"

/**
Classe repr�sentant l'action de se soigner
*/
class HealPlayerAction : public Action {
private:
	int const healFactor = 20;
public:
	explicit HealPlayerAction(int const tokenNb);
	int execute() override;
};