#pragma once
#include "Entity.h"
#include <string>


class Boat : public Entity {
public:
	explicit Boat(int const hp, int const maxHp);
};