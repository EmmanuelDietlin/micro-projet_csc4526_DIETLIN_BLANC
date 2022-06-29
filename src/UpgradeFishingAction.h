#include "Action.h"

/**
Classe représentant l'action d'améliorer la pêche
*/
class UpgradeFishingAction : public Action {
public:
	explicit UpgradeFishingAction(int const tokenNb, std::stringstream* recapText, int currentMaterials, int rodMaterialsRequired);
	int execute() override;
private:
	int const upgradeFactor = 1;
	int currentMaterials;
	int rodMaterialsRequired;
};