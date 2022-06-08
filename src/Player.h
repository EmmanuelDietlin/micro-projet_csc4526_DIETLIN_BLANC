#pragma once
#include "Entity.h"
#include <string>

/**
Classe repr�sentant l'entit� joueur.
*/
class Player : public Entity {
private:
	const std::string name;
public:
	Player(std::string const& name, int const hp, int const maxHp);
};