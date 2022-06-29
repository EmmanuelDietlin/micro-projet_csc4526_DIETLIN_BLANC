#include "UpgradeRowingAction.h"

/**
Execute l'action.
@return facteur d'améliration pour la pêche
*/
int UpgradeRowingAction::execute() {
	int rowingBonusToReturn = 0;
	if (tokenNb > 0 && currentMaterials >= boatMaterialsRequired) {
		rowingBonusToReturn += upgradeFactor;
		(*recapText) << "Avec les materiaux que vous avez recuperes, vous avez pu fabriquer de quoi mieux"
			<< " naviguer. Vous pourrez parcourir plus de distance avec votre barque !" << std::endl;
		(*recapText) << std::endl << "Bateau ameliore" << std::endl << std::endl;
	}
	return rowingBonusToReturn;
}

/**
Constructeur de la classe UpgradeRowingAction
@return tokenNb nombre de jetons de l'action
*/
UpgradeRowingAction::UpgradeRowingAction(int const tokenNb, std::stringstream* recapText, int currentMaterials, int boatMaterialsRequired) :
	Action(tokenNb, recapText),
	currentMaterials(currentMaterials),
	boatMaterialsRequired(boatMaterialsRequired)
{}
