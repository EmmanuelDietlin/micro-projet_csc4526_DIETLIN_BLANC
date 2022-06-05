#include "myMain.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <Windows.h>
#include <thread>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <memory>
#include "SFMLOrthogonalLayer.h"
#include "signals.h"


const int w_height = 800;
const int w_width = 1000;
const int maxDay = 47;
const int maxDistance = 6700;
const int playerBaseHp = 100;
const int boatBaseHp = 200;
const int spacing = 10;



void TextCentered(std::string const& s) {
    auto textWidth = ImGui::CalcTextSize(s.c_str()).x;
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - textWidth) * 0.5f);
    ImGui::Text(s.c_str());
}

void RemainingTokens(std::map<TokensType, int>& t, TokensType const& type) {
    int r;
    r = t[TokensType::tokenNbr];
    for (auto it : t) {
        if (it.first != TokensType::tokenNbr && it.first != TokensType::remainingTokens) {
            r -= it.second;
        }
    }
    if (t[type] < 0) {
        r += t[type];
        t[type] = 0;
    }
    if (r < 0) {
        t[type] += r;
        r = 0;
    }
    t[TokensType::remainingTokens] = r;
}

void ImGuiYSpacing() {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing);
}

void FadeToBlack(int& f) {
    f = 0;
}

bool SetMenuWindow(std::string const& title, std::string const& txt1, std::string const& txt2,
	std::string const& b_label) {
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0.5f, 0.5f));
	ImGui::SetNextWindowPos(sf::Vector2f(0, 0));
	ImGui::SetNextWindowSize(sf::Vector2f(w_width, w_height));
	ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

	ImGui::SetCursorPosY(w_height * 0.2f);
	ImGui::SetWindowFontScale(5);
	TextCentered(txt1);
	TextCentered(txt2);
	ImGui::SetWindowFontScale(1.3f);
	ImGui::SetCursorPos(sf::Vector2f(w_width / 2 - 100, w_height / 2 - 50));
	if (ImGui::Button(b_label.c_str(), sf::Vector2f(200, 100))) {
		return true;
	}

	return false;
}
void readRecap(std::stringstream& s) {
    s.str(std::string());   
    std::ifstream recapFile("resources/recap.txt");
    s << recapFile.rdbuf();
    recapFile.close();
}





int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    ImGui::SFML::Init(window);
    sf::Clock globalClock;
    sf::Clock deltaClock;
    sf::Clock faderClock;
    auto imguiWindow = ImGuiWindow::mainMenu;

    std::stringstream recapText;
    bool upgradeFishing = false;
    bool upgradeRowing = false;


    std::unique_ptr<Façade> façade;
    int fade_counter = 256;
    sf::RectangleShape fader(sf::Vector2f(w_width, w_height));
    fader.setFillColor(sf::Color(0,0,0,0));

    tmx::Map mainMenubg;
    mainMenubg.load("resources/mainMenubg.tmx");
    MapLayer mainMenuLayer1(mainMenubg, 0);

    std::vector<sf::Image> sprites;
    sf::Image i;
    i.loadFromFile("resources/sprites/boy_1.png");
    sprites.push_back(i);
    i.loadFromFile("resources/sprites/boy_2.png");
    sprites.push_back(i);
    i.loadFromFile("resources/sprites/boy_3.png");
    sprites.push_back(i);
    i.loadFromFile("resources/sprites/boy_4.png");
    sprites.push_back(i);

    sf::Texture playerTexture;
    playerTexture.loadFromImage(sprites[0]);
    int spriteIndex = 0;
    sf::RectangleShape player(sf::Vector2f(70, 70));
    player.setPosition(sf::Vector2f(710, 390));
    player.setTexture(&playerTexture);

    auto spriteClock = globalClock.getElapsedTime();

    tmx::Map map;
    map.load("resources/game_background.tmx");

    MapLayer layerBackground(map, 0);
    MapLayer layerBoat(map, 1);
    MapLayer layerForeground(map, 2);

    std::map<TokensType, int> tokens;
    tokens[TokensType::tokenNbr] = 0;
    tokens[TokensType::fishingsTokens] = 0;
    tokens[TokensType::rowingTokens] = 0;
    tokens[TokensType::healingTokens] = 0;
    tokens[TokensType::repairTokens] = 0;
    tokens[TokensType::remainingTokens] = 0;
    tokens[TokensType::upgradeFishingToken] = 0;
    tokens[TokensType::upgradeRowingToken] = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (imguiWindow != ImGuiWindow::mainMenu) {
                FadeToBlack(fade_counter);
                imguiWindow = ImGuiWindow::mainMenu;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        if (imguiWindow == ImGuiWindow::mainMenu) {
            if (SetMenuWindow("Main menu", "Les revoltes", "de la Bounty",
                "Commencer la partie")) {
                FadeToBlack(fade_counter);
                façade = std::make_unique<Façade>(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp);
                tokens[TokensType::tokenNbr] = façade->getTokenNbr();
                tokens[TokensType::remainingTokens] = façade->getTokenNbr();
                readRecap(recapText);
                imguiWindow = ImGuiWindow::gameWindow1;
            }
            ImGuiYSpacing();
            ImGui::SetCursorPosX(w_width / 2 - 100);
            if (façade) {
                if (ImGui::Button("Continuer la partie", sf::Vector2f(200, 100))) {
                    FadeToBlack(fade_counter);
                    imguiWindow = ImGuiWindow::gameWindow1;
                }
            }
            ImGuiYSpacing();
            ImGui::SetCursorPosX(w_width / 2 - 100);
            if (ImGui::Button("Quitter le jeu", sf::Vector2f(200, 100))) {
                window.close();
            }
            ImGui::End();
            ImGui::PopStyleColor(2);
            window.draw(mainMenuLayer1);
            ImGui::SFML::Render(window);

        }
        else if (imguiWindow == ImGuiWindow::gameWindow1 || imguiWindow == ImGuiWindow::gameWindow2) {
            ImGui::SetNextWindowPos(sf::Vector2f(41, 59));
            ImGui::SetNextWindowSize(sf::Vector2f(425, 600));

            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5f));
            ImGui::Begin("Logs", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoResize);
            ImGui::SetWindowFontScale(3);
            TextCentered("Jour " + std::to_string(façade->getDayCount()));
            ImGui::SetWindowFontScale(1.3f);
            ImGuiYSpacing();

			if (imguiWindow == ImGuiWindow::gameWindow1) {
				ImGui::TextWrapped(recapText.str().c_str());
				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
				if (ImGui::Button("Page suivante")) {
					imguiWindow = ImGuiWindow::gameWindow2;
				}
			}
			else if (imguiWindow == ImGuiWindow::gameWindow2) {
				ImGui::Text("Distance parcourue : %d km", façade->getDistanceTravelled());
				ImGui::ProgressBar((float)façade->getDistanceTravelled() / (float)maxDistance);
				ImGuiYSpacing();
				ImGui::Text("Jetons restants : %d", tokens[TokensType::remainingTokens]);
				if (ImGui::InputInt("Pecher", &tokens[TokensType::fishingsTokens], 1)) {
					RemainingTokens(tokens, TokensType::fishingsTokens);
				}
				if (ImGui::InputInt("Ramer", &tokens[TokensType::rowingTokens], 1)) {
					RemainingTokens(tokens, TokensType::rowingTokens);
				}
				if (ImGui::InputInt("Se soigner", &tokens[TokensType::healingTokens], 1)) {
					RemainingTokens(tokens, TokensType::healingTokens);
				}
				if (ImGui::InputInt("Reparer", &tokens[TokensType::repairTokens], 1)) {
					RemainingTokens(tokens, TokensType::repairTokens);
				}
				ImGuiYSpacing();
				ImGui::Text("Poissons : %d", façade->getFishCount());
                ImGuiYSpacing();
                ImGui::Text("Materiaux : %d", 0);
                ImGuiYSpacing();
                float cursor_y = ImGui::GetCursorPosY();
                if (ImGui::Checkbox("Ameliorer peche", &upgradeFishing)) {
                    if ((upgradeRowing && façade->getMaterials() - rod_materials_required - boat_materials_required < 0) ||
                        (!upgradeRowing && façade->getMaterials() < rod_materials_required)) {
                        upgradeFishing = false;
                    }
                    upgradeFishing ? tokens[TokensType::upgradeFishingToken] = 1 : tokens[TokensType::upgradeFishingToken] = 0;
                    RemainingTokens(tokens, TokensType::upgradeFishingToken);
                }
                ImGui::Text("Cout : %d", rod_materials_required);
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f);
                ImGui::SetCursorPosY(cursor_y);
                if (ImGui::Checkbox("Ameliorer bateau", &upgradeRowing)) {
                    if ((upgradeFishing && façade->getMaterials() - rod_materials_required - boat_materials_required < 0) ||
                        (!upgradeFishing && façade->getMaterials() < boat_materials_required)) {
                        upgradeRowing = false;
                    }
                    upgradeRowing ? tokens[TokensType::upgradeRowingToken] = 1 : tokens[TokensType::upgradeRowingToken] = 0;
                    RemainingTokens(tokens, TokensType::upgradeRowingToken);
                }
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f);
                ImGui::Text("Cout : %d", boat_materials_required);

				ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 160) * 0.5f);
				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 180);
				if (ImGui::Button("Jour suivant", ImVec2(160, 90))) {
					FadeToBlack(fade_counter);
                    auto ret = façade->nextDay(tokens);
					readRecap(recapText);
                    if (ret == Status::onGoing)
                        imguiWindow = ImGuiWindow::gameWindow1;
                    else if (ret == Status::victory)
                        imguiWindow = ImGuiWindow::victory;
                    else if (ret == Status::defeat)
                        imguiWindow = ImGuiWindow::defeat;
				}
				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
				if (ImGui::Button("Page precedente")) {
					imguiWindow = ImGuiWindow::gameWindow1;
				}
			}
			ImGui::PopStyleColor(1);
			ImGui::End();


            ImGui::SetNextWindowPos(sf::Vector2f(650, 300));
            ImGui::SetNextWindowSize(sf::Vector2f(150, 100));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5f));

            ImGui::Begin("Player", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            ImGui::Text("Pv joueur");
            ImGui::ProgressBar((float)façade->getPlayerHp() / (float)playerBaseHp);
            ImGui::Text("Pv bateau");
            ImGui::ProgressBar((float)façade->getBoatHp() / (float)boatBaseHp);
            ImGui::End();
            ImGui::PopStyleColor(1);


            
            if (globalClock.getElapsedTime() - spriteClock > sf::seconds(0.5f)) {
                spriteClock = globalClock.getElapsedTime();
                spriteIndex = (spriteIndex + 1) % 4;
                playerTexture.loadFromImage(sprites[spriteIndex]);
            }
            window.clear(sf::Color::Black);
            window.draw(layerBackground);
            window.draw(layerBoat);
            window.draw(layerForeground);
            window.draw(player);

            ImGui::SFML::Render(window);
        }
        else if (imguiWindow == ImGuiWindow::victory) {
            if (SetMenuWindow("Victory screen", "Vous avez", "gagne !",
                "Retour au menu")) {
                FadeToBlack(fade_counter);
                façade.reset();
                imguiWindow = ImGuiWindow::mainMenu;
            }
            ImGui::End();
            ImGui::PopStyleColor(2);
            ImGui::SFML::Render(window);
        }
        else if (imguiWindow == ImGuiWindow::defeat) {
            if (SetMenuWindow("Defeat screen", "Vous avez", "perdu !",
                "Retour au menu")) {
                FadeToBlack(fade_counter);
                façade.reset();
                imguiWindow = ImGuiWindow::mainMenu;
            }
            ImGui::End();
            ImGui::PopStyleColor(2);
            ImGui::SFML::Render(window);
        }
        else if (imguiWindow == ImGuiWindow::informations) {
            //A implémenter
        }

        if (faderClock.getElapsedTime() > sf::seconds(0.005f) && fade_counter < 256) {
            fader.setFillColor(sf::Color(0, 0, 0, 255-fade_counter));
            fade_counter++;
            faderClock.restart();
        }

        window.draw(fader);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
