#pragma once
#include "Entity.h"
#include <string>

/**
Classe repr�sentant le bateau du joueur. 
H�rite de Entity.
*/
class Boat : public Entity {
public:
	explicit Boat(int const hp, int const maxHp);
};