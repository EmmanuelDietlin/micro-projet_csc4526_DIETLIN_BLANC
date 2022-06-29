#include "RowingAction.h"

/**
Constructeur de la classe RowingAction
@param tokenNb nombre de jetons de l'action
*/
RowingAction::RowingAction(int const tokenNb, std::stringstream* recapText, int const rowingBonus, Boat* boat) :
	Action(tokenNb, recapText),
	rowingBonus(rowingBonus),
	boat(boat)
	{}

/**
Execute l'action
@return renvoie la distance parcourue.
*/
int RowingAction::execute() {
	int toks = tokenNb;
	int distanceToReturn = 0;
	if (boat->stronglyDamaged()) {
		toks--;
		(*recapText) << "L'etat du bateau rend difficile la naviguation !"
			<< std::endl << "Distance parcourue reduite" << std::endl << std::endl;
	}
	if (toks > 0) {
		distanceToReturn += rowingBonus + ((toks + Action::random_int(-1, 1)) * baseDistance);
	}

	if (distanceToReturn > 0) {
		if (distanceToReturn < 200) {
			(*recapText) << "Une combinaison de vents defavorables et de mer calme vous ont conduit a ne parcourir qu'une"
				<< " courte distance, diminuant donc vos chances de parvenir a votre objectif dans le temps imparti..." << std::endl;
		}
		else {
			(*recapText) << "Des vents favorables et de bonnes decisions de votre part vous permettent de parcourir une grande distance."
				<< " A ce rythme, l'objectif sera surement atteint rapidement !" << std::endl;
		}
		(*recapText) << std::endl << "Distance parcourue : " << distanceToReturn << " km" << std::endl << std::endl;
	}
	return distanceToReturn;
}