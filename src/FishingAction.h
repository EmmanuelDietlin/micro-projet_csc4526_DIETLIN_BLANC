#include "Action.h"

/**
Classe repr�sentant l'action de p�cher.
*/
class FishingAction : public Action {
private:
	int baseFishRate = 1;
public:
	explicit FishingAction(int const tokenNb);
	int execute() override;
};

