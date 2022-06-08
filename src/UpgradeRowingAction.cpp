#include "UpgradeRowingAction.h"

/**
Execute l'action.
@return facteur d'am�liration pour la p�che
*/
int UpgradeRowingAction::execute() {
	return upgradeFactor;
}

/**
Constructeur de la classe UpgradeRowingAction
@return tokenNb nombre de jetons de l'action
*/
UpgradeRowingAction::UpgradeRowingAction(int const tokenNb) : Action(tokenNb) {}
