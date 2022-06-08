#include "UpgradeFishingAction.h"

/**
Execute l'action.
@return facteur d'am�lioration pour la p�che
*/
int UpgradeFishingAction::execute() {
	return upgradeFactor;
}

/**
Constructeur de la classe UpgradeFishingAction
@param tokenNb nombre de jetons pour l'action
*/
UpgradeFishingAction::UpgradeFishingAction(int const tokenNb) : Action(tokenNb) {}