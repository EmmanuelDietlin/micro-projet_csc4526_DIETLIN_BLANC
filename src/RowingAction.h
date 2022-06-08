#include "Action.h"

/**
Classe repr�sentant l'action de ramer/naviguer
*/
class RowingAction : public Action {
private:
	int baseDistance = 100;
public:
	explicit RowingAction(int const tokenNb);
	int execute() override;
};