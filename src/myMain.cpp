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
#include "SFMLOrthogonalLayer.h"
#include "Façade.h"


const int w_height = 800;
const int w_width = 1000;
const int maxDay = 47;
const int maxDistance = 6700;
const int playerBaseHp = 100;
const int boatBaseHp = 200;

void textCentered(std::string const& s) {
    auto textWidth = ImGui::CalcTextSize(s.c_str()).x;
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - textWidth) * 0.5f);
    ImGui::Text(s.c_str());
}

void remainingTokens(std::map<TokensType, int>& t, TokensType const& type) {
    int r = t[TokensType::tokenNbr];
    for (auto it : t) {
        if (it.first != TokensType::tokenNbr && it.first != TokensType::remainingTokens) {
            r -= it.second;
        }
    }
    if (r < 0) {
        t[type] += r;
        r = 0;
    }
    t[TokensType::remainingTokens] = r;
}


int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    ImGui::SFML::Init(window);
    sf::Clock globalClock;
    sf::Clock deltaClock;
    sf::Clock faderClock;
    ImGuiWindow imguiWindow = ImGuiWindow::mainMenu;

    Façade façade(maxDay, maxDistance, playerBaseHp, boatBaseHp);
    int fade_counter = 512;
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
    tokens[TokensType::tokenNbr] = façade.getTokenNbr();
    tokens[TokensType::fishingsTokens] = 0;
    tokens[TokensType::rowingTokens] = 0;
    tokens[TokensType::healingTokens] = 0;
    tokens[TokensType::repairTokens] = 0;
    tokens[TokensType::remainingTokens] = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        if (imguiWindow == ImGuiWindow::mainMenu) {
            ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0.5f, 0.5f));
            ImGui::SetNextWindowPos(sf::Vector2f(0, 0));
            ImGui::SetNextWindowSize(sf::Vector2f(w_width, w_height));
            ImGui::Begin("Main Menu", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
            
            ImGui::SetCursorPosY(w_height*0.2f);
            ImGui::SetWindowFontScale(5);
            textCentered("Les revoltes");
            textCentered("de la Bounty");
            ImGui::SetWindowFontScale(1.3f);
            ImGui::SetCursorPos(sf::Vector2f(w_width/2-100,w_height/2-50));
            if (ImGui::Button("Commencer la partie", sf::Vector2f(200,100))) {
                imguiWindow = ImGuiWindow::gameWindow1;
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
            if (imguiWindow == ImGuiWindow::gameWindow1) {
                ImGui::Text("Texte decrivant les evenements s'etant \nderoules la journee precedente");
                if (ImGui::Button("Page suivante")) {
                    imguiWindow = ImGuiWindow::gameWindow2;
                }
            } 
            else if (imguiWindow == ImGuiWindow::gameWindow2) {
                ImGui::Text("Jour %d", façade.getDayCount());
                ImGui::Text("Distance parcourue : %d km", façade.getDistanceTravelled());
                ImGui::Text("Jetons restants : %d", remainingTokens);
                ImGui::ProgressBar((float)façade.getDistanceTravelled() / (float)maxDistance);
                if (ImGui::InputInt("Nombre de jetons\npour pecher", &tokens[TokensType::fishingsTokens], 1)) {
                    remainingTokens(tokens, TokensType::fishingsTokens);
                }
                if (ImGui::InputInt("Nombre de jetons\npour ramer", &tokens[TokensType::rowingTokens], 1)) {
                    remainingTokens(tokens, TokensType::rowingTokens);
                }
                if (ImGui::InputInt("Nombre de jetons\npour se soigner", &tokens[TokensType::healingTokens], 1)) {
                    remainingTokens(tokens, TokensType::healingTokens);
                }
                if (ImGui::InputInt("Nombre de jetons\npour reparer", &tokens[TokensType::repairTokens], 1)) {
                    remainingTokens(tokens, TokensType::repairTokens);
                }
                ImGui::Text("Poissons : %d", façade.getFishCount());
                if (ImGui::Button("Jour suivant")) {
                    façade.executeFishingAction(tokens[TokensType::fishingsTokens]);
                    façade.executeRowingAction(tokens[TokensType::rowingTokens]);
                    façade.executeHealingAction(tokens[TokensType::healingTokens]);
                    façade.executeRepairAction(tokens[TokensType::repairTokens]);
                    façade.nextDay();
                    fade_counter = 0;
                }
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
            //ImGui::Text("Hp : %d/%d", façade.getPlayerHp(), playerBaseHp);
            ImGui::Text("Pv joueur");
            ImGui::ProgressBar((float)façade.getPlayerHp() / (float)playerBaseHp);
            ImGui::Text("Pv bateau");
            ImGui::ProgressBar((float)façade.getBoatHp() / (float)boatBaseHp);
            ImGui::End();
            ImGui::PopStyleColor(1);


            
            if (globalClock.getElapsedTime() - spriteClock > sf::seconds(0.5f)) {
                spriteClock = globalClock.getElapsedTime();
                spriteIndex = (spriteIndex + 1) % 4;
                playerTexture.loadFromImage(sprites[spriteIndex]);
            }

            if (faderClock.getElapsedTime() > sf::seconds(0.001f) && fade_counter < 512) {
                if (fade_counter < 256)
                    fader.setFillColor(sf::Color(0, 0, 0, fade_counter));
                else
                    fader.setFillColor(sf::Color(0, 0, 0, 511 - fade_counter));
                fade_counter++;
                faderClock.restart();
            }




            window.clear(sf::Color::Black);
            window.draw(layerBackground);
            window.draw(layerBoat);
            window.draw(layerForeground);
            window.draw(player);

            ImGui::SFML::Render(window);
            window.draw(fader);
        }
        else if (imguiWindow == ImGuiWindow::victory) {

        }
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}