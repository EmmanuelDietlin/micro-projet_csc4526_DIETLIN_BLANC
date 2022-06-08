#include "RowingAction.h"

/**
Constructeur de la classe RowingAction
@param tokenNb nombre de jetons de l'action
*/
RowingAction::RowingAction(int const tokenNb) : Action(tokenNb) {}

/**
Execute l'action
@return renvoie la distance parcourue.
*/
int RowingAction::execute() {
	return (tokenNb + Action::random_int(-1, 1)) * baseDistance ;
}