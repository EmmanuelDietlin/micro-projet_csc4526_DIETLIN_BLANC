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


    tmx::Map map;
    map.load("resources/game_background.tmx");

    MapLayer layerBackground(map, 0);
    MapLayer layerBoat(map, 1);
    MapLayer layerForeground(map, 2);
    MapLayer layerGui1(map, 3);
    MapLayer layerGui2(map, 4);

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

        ImGui::Begin("Journal de bord");
        ImGui::Text("Day %d", façade.getDayCount());
        ImGui::Text("Distance travelled : %d km", façade.getDistanceTravelled());
        ImGui::ProgressBar(façade.getDistanceTravelled() / distance);
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
        }
        ImGui::End();

        window.clear(sf::Color::Black);
        window.draw(layerBackground);
        window.draw(layerBoat);
        window.draw(layerForeground);
        window.draw(layerGui1);
        window.draw(layerGui2);

        ImGui::SFML::Render(window);
        window.display();

    }
    ImGui::SFML::Shutdown();
    return 0;
}