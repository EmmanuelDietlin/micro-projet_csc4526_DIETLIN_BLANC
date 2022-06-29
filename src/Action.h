#pragma once
#include <random>
#include <sstream>

/**
Classe abstraite Action.

Peut être exécutée en appelant execute(). 
Est utilisée comme classe parente pour toutes les différentes actions du jeu.

*/
class Action {
public:
	virtual ~Action() = default;
	virtual int execute() = 0;
	void addTokens(int const tokens);
	void clearTokens();
	int getTokenNb() const ;
protected:
	explicit Action(int const tokenNb, std::stringstream* recapText);
	int random_int(int const start, int const end);
	int tokenNb;
	std::stringstream* recapText;
};