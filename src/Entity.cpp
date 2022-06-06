#include "Entity.h"
#include <algorithm>
#include <iostream>

Entity::Entity(int const hp, int const maxHp) : hp(hp), maxHp(maxHp)
{}

void Entity::takeDamage(int const dmg) {
	hp.fetch_sub(dmg);
}

void Entity::heal(int const heal) {
	hp > (maxHp - heal) ? hp = maxHp : hp.fetch_add(heal);
}

int Entity::getHp() {
	return hp;
}