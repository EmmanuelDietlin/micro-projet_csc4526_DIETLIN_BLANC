#pragma once
#include "signals.h"
#include <atomic>

class Entity {
private:
	std::atomic<int> hp;
	int maxHp;
protected:
	explicit Entity(int const hp, int const maxHp);
	void takeDamage(int const dmg);
	void heal(int const heal);
	int getHp();
};