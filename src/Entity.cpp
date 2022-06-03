#include "Entity.h"
#include <algorithm>

Entity::Entity(int const hp, int const maxHp) : hp(hp), maxHp(maxHp)
{}

void Entity::takeDamage(int const dmg) {
	hp -= dmg;
	if (dmg < 0) {
		//indiquer que le joueur est mort
	}
}

void Entity::heal(int const heal) {
	hp = std::min(hp + heal, maxHp);
}

int Entity::getHp() {
	return hp;
}