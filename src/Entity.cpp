#include "Entity.h"
#include <algorithm>
#include <iostream>

/**
Constructeur de la classe Entity
@param hp pv de l'entit�
@param maxHp pv max de l'entit�
*/
Entity::Entity(int const hp, int const maxHp) : hp(hp), maxHp(maxHp)
{}

/**
Inflige des dommages � l'entit�.
@param dmg quantit� de d�g�ts � infliger
*/
void Entity::takeDamage(int const dmg) {
	hp.fetch_sub(dmg);
}
/**
Soigne l'entit�.
@param heal quantit� de pv � donner
*/
void Entity::heal(int const heal) {
	hp > (maxHp - heal) ? hp = maxHp : hp.fetch_add(heal);
}
/**
*Renvoie les pv de l'entit�.
* @return pv de l'entit�.
*/
int Entity::getHp() {
	return hp;
}