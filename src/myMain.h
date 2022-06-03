#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum class ImGuiWindow { mainMenu, gameWindow1, gameWindow2, victory, defeat };
enum class TokensType { tokenNbr, fishingsTokens, rowingTokens, healingTokens, repairTokens, remainingTokens };

int myMain();
void TextCentered(std::string const &s);
void RemainingTokens(std::map<TokensType, int>& t, TokensType const &type);
void ImGuiYSpacing();
void FadeToBlack(int &f);
