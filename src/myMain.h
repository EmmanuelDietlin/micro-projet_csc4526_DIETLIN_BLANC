#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum class ImGuiWindow { mainMenu, gameWindow1, gameWindow2, victory, defeat };
enum class TokensType { tokenNbr, fishingsTokens, rowingTokens, healingTokens, repairTokens, remainingTokens };

int myMain();
void textCentered(std::string const &s);
void remainingTokens(std::map<TokensType, int>& t, TokensType const &type);
