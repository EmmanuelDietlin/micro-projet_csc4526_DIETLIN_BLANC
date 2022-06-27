#include "UpgradeFishingAction.h"

/**
Execute l'action.
@return facteur d'amélioration pour la pêche
*/
int UpgradeFishingAction::execute() {
	int fishingBonusToReturn = 0;
	if (tokenNb > 0 && currentMaterials >= rodMaterialsRequired) {
		fishingBonusToReturn += upgradeFactor;
		(*recapText) << "Avec les materiaux que vous avez recuperes, vous avez pu fabriquer une canne "
			<< " a peche. Cela vous permettra de recolter plus de poisson !" << std::endl;
		(*recapText) << std::endl << "Canne a peche + 1" << std::endl << std::endl;
	}
	return fishingBonusToReturn;
}

/**
Constructeur de la classe UpgradeFishingAction
@param tokenNb nombre de jetons pour l'action
*/
UpgradeFishingAction::UpgradeFishingAction(int const tokenNb, std::stringstream* recapText, int currentMaterials, int rodMaterialsRequired) :
	Action(tokenNb, recapText),
	currentMaterials(currentMaterials),
	rodMaterialsRequired(rodMaterialsRequired)
	{}