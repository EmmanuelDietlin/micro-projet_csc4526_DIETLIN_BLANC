#include "RepairBoatAction.h"

/**
Constructeur de la classe RepairBoatAction
@param tokenNb nombre de jetons de l'action
*/
RepairBoatAction::RepairBoatAction(int const tokenNb, std::stringstream* recapText) : Action(tokenNb, recapText) {}

/**
Execute l'action.
@return nombre de points de vie à restaurer au bateau.
*/
int RepairBoatAction::execute() {
	int healToReturn = 0;
	if (tokenNb > 0) {
		healToReturn += tokenNb * repairFactor;
		(*recapText) << "Reparer l'embarcation est une sage idee pour eviter de se retrouver au milieu"
			<< " de l'ocean accroche a une planche pour tenter de se maintenir a flot." << std::endl;
		(*recapText) << std::endl << "Reparations : " << healToReturn << std::endl << std::endl;
	}
	return healToReturn;
}