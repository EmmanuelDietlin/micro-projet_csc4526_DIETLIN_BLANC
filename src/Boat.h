#pragma once
#include "Entity.h"
#include <string>

/**
Classe représentant le bateau du joueur. 
Hérite de Entity.
*/
class Boat : public Entity {
public:
	explicit Boat(int const hp, int const maxHp);
};