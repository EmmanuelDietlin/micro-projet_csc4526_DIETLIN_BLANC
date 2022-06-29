#include "HealPlayerAction.h"

/**
Constructeur de la classe HealPlayerAction.
@param tokenNb nombre de jetons pour l'action
*/
HealPlayerAction::HealPlayerAction(int const tokenNb, std::stringstream* recapText) : Action(tokenNb, recapText) {}

/**
*Execute l'action.
* return nombre de points de vie restaurés.
*/
int HealPlayerAction::execute() {
	int healToReturn = 0;
	if (tokenNb > 0) {
		healToReturn += tokenNb * healFactor;
		(*recapText) << "Un peu de repos ne fait pas de mal ! En vous reposant, vous avez pu recuperer"
			<< " une partie de votre energie" << std::endl;
		(*recapText) << std::endl << "Vie : +" << healToReturn << std::endl << std::endl;
	}
	return healToReturn;
}
