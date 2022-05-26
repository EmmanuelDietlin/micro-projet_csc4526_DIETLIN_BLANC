#pragma once

const int MaxHP = 100;

class Entity {
private:
	int hp;
public:
	explicit Entity(int const hp);
	void takeDamage(int const dmg);
	void heal(int const heal);
};