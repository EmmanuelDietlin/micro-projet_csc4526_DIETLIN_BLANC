#include "Player.h"
/**
* Constructeur de la classe Player.
* @param name nom du joueur
* @param hp nombre de points de vie du joueur
* @param maxHp points de vie max du joueur
*/
Player::Player(std::string const& name, int const hp, int const maxHp) : Entity(hp, maxHp), name(name) {}