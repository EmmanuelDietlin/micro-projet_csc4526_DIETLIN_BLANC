#include "FishingAction.h"

/**
*Constructeur de la classe FishingAction.
* @param tokenNb nombre de jetons pour l'action
*/
FishingAction::FishingAction(int const tokenNb) : Action(tokenNb) {}

/**
* Execute l'action.
* @return nombre de poissons pêchés.
*/
int FishingAction::execute() {
	int f = 0;
	for (int i = 0; i < tokenNb; i++) {
		f += Action::random_int(0, 2);
	}
	return f ;
}