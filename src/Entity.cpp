#include "Entity.h"
#include <algorithm>
#include <iostream>

/**
Constructeur de la classe Entity
@param hp pv de l'entité
@param maxHp pv max de l'entité
*/
Entity::Entity(int const hp, int const maxHp) : hp(hp), maxHp(maxHp)
{}

/**
Inflige des dommages à l'entité.
@param dmg quantité de dégâts à infliger
*/
void Entity::takeDamage(int const dmg) {
	hp.fetch_sub(dmg);
}
/**
Soigne l'entité.
@param heal quantité de pv à donner
*/
void Entity::heal(int const heal) {
	hp > (maxHp - heal) ? hp = maxHp : hp.fetch_add(heal);
}
/**
*Renvoie les pv de l'entité.
* @return pv de l'entité.
*/
int Entity::getHp() {
	return hp;
}