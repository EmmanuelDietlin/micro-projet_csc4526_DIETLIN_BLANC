#include "UpgradeRowingAction.h"

/**
Execute l'action.
@return facteur d'améliration pour la pêche
*/
int UpgradeRowingAction::execute() {
	return upgradeFactor;
}

/**
Constructeur de la classe UpgradeRowingAction
@return tokenNb nombre de jetons de l'action
*/
UpgradeRowingAction::UpgradeRowingAction(int const tokenNb) : Action(tokenNb) {}
