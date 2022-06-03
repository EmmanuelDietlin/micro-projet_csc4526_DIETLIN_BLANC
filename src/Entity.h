#pragma once


class Entity {
private:
	int hp;
	int maxHp;
public:
	explicit Entity(int const hp, int const maxHp);
	void takeDamage(int const dmg);
	void heal(int const heal);
	int getHp();
};