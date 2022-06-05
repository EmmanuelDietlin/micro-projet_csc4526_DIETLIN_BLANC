#include "Entity.h"
#include <algorithm>
#include <iostream>

Entity::Entity(int const hp, int const maxHp) : hp(hp), maxHp(maxHp)
{}

void Entity::takeDamage(int const dmg) {
	hp -= dmg;
}

void Entity::heal(int const heal) {
	hp = std::min(hp + heal, maxHp);
}

int Entity::getHp() {
	return hp;
}