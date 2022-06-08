#include "Action.h"
/**
* Constructeur de la classe Action
* @param tokenNb nombre de jetons pour l'action
*/
Action::Action(int const tokenNb) : tokenNb(tokenNb) {}

/**
* Ajoute des tokens à l'action
* @param tokens nombre de jetons à ajouter
*/
void Action::addTokens(int const tokens) {
	tokenNb = tokens;
}


/**
* Réinitialise les jetons de l'action
*/
void Action::clearTokens() {
	tokenNb = 0;
}


/**
* Renvoie le nombre de jetons de l'action
* @return nombre de jetons de l'action
*/
int Action::getTokenNb() const {
	return tokenNb;
}

/**
Génère un nombre aléatoire entre deux entiers, selon une distribution uniforme.
@param start entier de départ
@param end entier de fin
@return entier choisit aléatoirement
*/
int Action::random_int(int const start, int const end) {
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(start, end);
	return distribution(engine);
}
