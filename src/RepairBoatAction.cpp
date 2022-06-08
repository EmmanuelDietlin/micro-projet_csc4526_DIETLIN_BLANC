#include "RepairBoatAction.h"

/**
Constructeur de la classe RepairBoatAction
@param tokenNb nombre de jetons de l'action
*/
RepairBoatAction::RepairBoatAction(int const tokenNb) : Action(tokenNb) {}

/**
Execute l'action.
@return nombre de points de vie à restaurer au bateau.
*/
int RepairBoatAction::execute() {
	return repairFactor * tokenNb;
}