#include "Player.h"

Player::Player(std::string const& name, int const hp, int const maxHp) : Entity(hp, maxHp), name(name) {}