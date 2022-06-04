#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <sstream>

enum class ImGuiWindow { mainMenu, gameWindow1, gameWindow2, victory, defeat, informations };
enum class TokensType { tokenNbr, fishingsTokens, rowingTokens, healingTokens, repairTokens, remainingTokens };

int myMain();
void TextCentered(std::string const &s);
void RemainingTokens(std::map<TokensType, int>& t, TokensType const &type);
void ImGuiYSpacing();
void FadeToBlack(int &f);
bool SetMenuWindow(std::string const& title, std::string const& txt1, std::string const& txt2, 
	std::string const &b_label);
void readRecap(std::stringstream& s);
