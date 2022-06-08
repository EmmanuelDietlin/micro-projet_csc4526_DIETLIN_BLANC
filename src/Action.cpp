#include "Action.h"
/**
* Constructeur de la classe Action
* @param tokenNb nombre de jetons pour l'action
*/
Action::Action(int const tokenNb) : tokenNb(tokenNb) {}

/**
* Ajoute des tokens � l'action
* @param tokens nombre de jetons � ajouter
*/
void Action::addTokens(int const tokens) {
	tokenNb = tokens;
}


/**
* R�initialise les jetons de l'action
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
G�n�re un nombre al�atoire entre deux entiers, selon une distribution uniforme.
@param start entier de d�part
@param end entier de fin
@return entier choisit al�atoirement
*/
int Action::random_int(int const start, int const end) {
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(start, end);
	return distribution(engine);
}
