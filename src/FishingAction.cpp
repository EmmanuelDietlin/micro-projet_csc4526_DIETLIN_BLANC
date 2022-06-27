#include "FishingAction.h"

/**
*Constructeur de la classe FishingAction.
* @param tokenNb nombre de jetons pour l'action
*/
FishingAction::FishingAction(int const tokenNb, std::stringstream* recapText, int const fishingBonus, Player* player) :
	Action(tokenNb, recapText),
	fishingBonus(fishingBonus),
	player(player)
	{}

/**
* Execute l'action.
* @return nombre de poissons pêchés.
*/
int FishingAction::execute() {
	int toks = tokenNb;
	int nbfishToReturn = 0;
	if (player->stronglyDamaged()) {
		toks--;
		(*recapText) << "Du fait de votre etat, vous ne pouvez pas agir autant que vous le souhaitez !"
			<< std::endl << "Nombre de poissons peche diminue" << std::endl << std::endl;
	}
	if (toks > 0) {
		nbfishToReturn += fishingBonus;
		for (int i = 0; i < tokenNb; i++) {
			nbfishToReturn += Action::random_int(0, 2);
		}
	}

	if (nbfishToReturn < 3) {
		(*recapText) << "Vous avez lance votre ligne dans l'eau, mais la chance ne vous a pas sourit : seuls quelques malheureux"
			<< " poissons ont mordu a l'appat. Il va sans doute falloir vous rationner..." << std::endl;
	}
	else {
		(*recapText) << "La chance vous a sourit : vous n'avez eu qu'a lancer votre ligne dans l'eau, et aussitot de nombreux"
			<< " poissons se sont jetes dessus ! Sacre festin en perspective !" << std::endl;
	}
	(*recapText) << std::endl << "Poissons peches : " << nbfishToReturn << std::endl << std::endl;
	return nbfishToReturn;
}