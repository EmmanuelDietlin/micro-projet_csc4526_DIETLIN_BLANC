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
const int days = 47;
const int distance = 6700;



int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    ImGui::SFML::Init(window);
    sf::Clock globalClock;
    sf::Clock deltaClock;

    Façade façade;
    float opacity = 0;
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

        sf::Time duration = globalClock.getElapsedTime();
        layerBackground.update(duration);
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowPos(sf::Vector2f(41, 59));
        ImGui::SetNextWindowSize(sf::Vector2f(425, 600));

        ImGui::Begin("Journal de bord");
        ImGui::Text("Day %d", façade.getDayCount());
        ImGui::Text("Distance travelled : %d km", façade.getDistanceTravelled());
        ImGui::Text("Remaining tokens : %d", remainingTokens);
        ImGui::ProgressBar((float)façade.getDistanceTravelled() / (float)distance);
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
            while (opacity < 1) {
                window.draw(fader);
                window.display();
                fader.setFillColor(sf::Color(0, 0, 0, (int)(opacity * 255)));
                opacity += 0.001f;
            }
            while (opacity > 0) {
                window.draw(fader);
                window.display();
                fader.setFillColor(sf::Color(0, 0, 0, (int)(opacity * 255)));
                opacity -= 0.001f;
            }
        }
        ImGui::End();

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

        window.display();

    }
    ImGui::SFML::Shutdown();
    return 0;
}