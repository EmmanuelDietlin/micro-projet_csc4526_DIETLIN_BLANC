#pragma once
#include "signals.h"
#include <atomic>

/**
Classe abstraite représentant une entité.
Contient un champ hp représentant les points de vie et un champ maxHp contenant les 
points de vie maximum de l'entité.s
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