#pragma once
#include "pugixml.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <Shape.h>
#include <Group.h>

int myMain();
void printAsText(std::vector<std::pair<std::string, std::string>> &m, Group& g);
void printAsImage(Group& g, sf::RenderWindow& w);
