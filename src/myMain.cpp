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



int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    ImGui::SFML::Init(window);
    sf::Clock globalClock;
    sf::Clock deltaClock;

    Façade f();

    tmx::Map map;
    map.load("resources/game_background.tmx");

    MapLayer layerBackground(map, 0);
    MapLayer layerBoat(map, 1);
    MapLayer layerForeground(map, 2);
    MapLayer layerGui1(map, 3);
    MapLayer layerGui2(map, 4);

    sf::RectangleShape fishMinus(sf::Vector2f(50, 25));
    sf::RectangleShape fishPlus(sf::Vector2f(50, 25));
    sf::RectangleShape rowMinus(sf::Vector2f(50, 25));
    sf::RectangleShape rowPlus(sf::Vector2f(50, 25));

    fishMinus.setPosition(115, 305);
    fishPlus.setPosition(115, 403);
    rowMinus.setPosition(322, 305);
    rowPlus.setPosition(322, 403);

    int tokenNbr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (fishMinus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Button clicked" << std::endl;
                }
            }
        }
        sf::Time duration = globalClock.getElapsedTime();
        layerBackground.update(duration);
        ImGui::SFML::Update(window, deltaClock.restart());


        window.clear(sf::Color::Black);
        window.draw(layerBackground);
        window.draw(layerBoat);
        window.draw(layerForeground);
        window.draw(layerGui1);
        window.draw(layerGui2);

        window.draw(fishMinus);
        window.draw(fishPlus);
        window.draw(rowMinus);
        window.draw(rowPlus);

        ImGui::SFML::Render(window);
        window.display();

    }
    ImGui::SFML::Shutdown();
    return 0;
}