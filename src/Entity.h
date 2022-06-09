#pragma once
#include "signals.h"
#include <atomic>

/**
Classe abstraite repr�sentant une entit�.
Contient un champ hp repr�sentant les points de vie et un champ maxHp contenant les 
points de vie maximum de l'entit�.s
*/
class Entity {
private:
	std::atomic<int> hp;
	int maxHp;
protected:
	explicit Entity(int const hp, int const maxHp);
public:
	void takeDamage(int const dmg);
	void heal(int const heal);
	int getHp();
	bool stronglyDamaged();
};