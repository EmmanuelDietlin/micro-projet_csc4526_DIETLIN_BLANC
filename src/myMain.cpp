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



int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    ImGui::SFML::Init(window);
    sf::Clock globalClock;
    sf::Clock deltaClock;
    sf::Clock faderClock;
    int menu_nbr = 0;

    Façade façade(maxDay, maxDistance, playerBaseHp, boatBaseHp);
    int fade_counter = 512;
    sf::RectangleShape fader(sf::Vector2f(w_width, w_height));
    fader.setFillColor(sf::Color(0,0,0,0));

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

    sf::Time spriteClock;
    spriteClock = globalClock.getElapsedTime();

    tmx::Map map;
    map.load("resources/game_background.tmx");

    MapLayer layerBackground(map, 0);
    MapLayer layerBoat(map, 1);
    MapLayer layerForeground(map, 2);

    std::map<std::string, int> tokens;
    tokens["tokenNbr"] = façade.getTokenNbr();
    tokens["fishingTokens"] = 0;
    tokens["rowingTokens"] = 0;

    int remainingTokens = tokens["tokenNbr"] - tokens["fishingTokens"] - tokens["rowingTokens"];

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        if (menu_nbr == 0) {
            ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0, 0, 0, 0));
            ImGui::SetNextWindowPos(sf::Vector2f(0, 0));
            ImGui::SetNextWindowSize(sf::Vector2f(w_width, w_height));
            ImGui::Begin("Main Menu");
            ImGui::SetCursorPos(sf::Vector2f(w_width/2-100,w_height/2-50));
            if (ImGui::Button("Start game", sf::Vector2f(200,100))) {
                menu_nbr = 1;
            }
            ImGui::End();
            ImGui::PopStyleColor(1);

            window.clear(sf::Color::Black);
            ImGui::SFML::Render(window);
        }
        else {
            ImGui::SetNextWindowPos(sf::Vector2f(41, 59));
            ImGui::SetNextWindowSize(sf::Vector2f(425, 600));

            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5f));
            ImGui::Begin("Logs");
            if (menu_nbr == 1) {
                ImGui::Text("Texte decrivant les evenements s'etant \nderoules la journee precedente");
                if (ImGui::Button("Next page")) {
                    menu_nbr = 2;
                }
            } 
            else if (menu_nbr == 2) {
                ImGui::Text("Day %d", façade.getDayCount());
                ImGui::Text("Distance travelled : %d km", façade.getDistanceTravelled());
                ImGui::Text("Remaining tokens : %d", remainingTokens);
                ImGui::ProgressBar((float)façade.getDistanceTravelled() / (float)maxDistance);
                if (ImGui::InputInt("Number of tokens\nfor fishing", &tokens["fishingTokens"], 1)) {
                    remainingTokens = tokens["tokenNbr"] - tokens["rowingTokens"] - tokens["fishingTokens"];
                    if (remainingTokens < 0) {
                        tokens["fishingTokens"] += remainingTokens;
                        remainingTokens = 0;
                    }
                }
                if (ImGui::InputInt("Number of tokens\nfor rowing", &tokens["rowingTokens"], 1)) {
                    remainingTokens = tokens["tokenNbr"] - tokens["rowingTokens"] - tokens["fishingTokens"];
                    if (remainingTokens < 0) {
                        tokens["rowingTokens"] += remainingTokens;
                        remainingTokens = 0;
                    }
                }
                ImGui::Text("Fishes : %d", façade.getFishCount());
                if (ImGui::Button("Next day")) {
                    façade.executeRowingAction(tokens["rowingTokens"]);
                    façade.executeFishingAction(tokens["fishingTokens"]);
                    façade.nextDay();
                    fade_counter = 0;
                }
                if (ImGui::Button("Previous page")) {
                    menu_nbr = 1;
                }
            }
            ImGui::PopStyleColor(1);
            ImGui::End();
            


            ImGui::SetNextWindowPos(sf::Vector2f(650, 300));
            ImGui::SetNextWindowSize(sf::Vector2f(150, 80));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5f));

            ImGui::Begin("Player");
            //ImGui::Text("Hp : %d/%d", façade.getPlayerHp(), playerBaseHp);
            ImGui::ProgressBar((float)façade.getPlayerHp() / (float)playerBaseHp);
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


        window.display();


    }
    ImGui::SFML::Shutdown();
    return 0;
}