#include "HealPlayerAction.h"

/**
Constructeur de la classe HealPlayerAction.
@param tokenNb nombre de jetons pour l'action
*/
HealPlayerAction::HealPlayerAction(int const tokenNb) : Action(tokenNb) {}

/**
*Execute l'action.
* return nombre de points de vie restaurés.
*/
int HealPlayerAction::execute() {
	return tokenNb * healFactor;
}
