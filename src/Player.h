#pragma once
#include "Entity.h"
#include <string>

class Player : public Entity {
private:
	const std::string name;
public:
	Player(std::string const& name, int const hp);
};