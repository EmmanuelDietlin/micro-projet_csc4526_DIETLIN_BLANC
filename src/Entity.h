#pragma once
#include "signals.h"

class Entity {
private:
	int hp;
	int maxHp;
public:
	vdk::signal<void(void)> deathSignal;
	explicit Entity(int const hp, int const maxHp);
	void takeDamage(int const dmg);
	void heal(int const heal);
	int getHp();
};