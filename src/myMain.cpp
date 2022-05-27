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


const int w_height = 800;
const int w_width = 1000;



int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    ImGui::SFML::Init(window);
    sf::Clock globalClock;
    sf::Clock deltaClock;

    tmx::Map map;
    map.load("resources/game_background.tmx");

    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);
    MapLayer layerTwo(map, 2);

    sf::RectangleShape button1(sf::Vector2f(50, 20));
    button1.setPosition(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if (button1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition()))) {
                    std::cout << "Button clicked" << std::endl;
                }
            }
        }
        sf::Time duration = globalClock.getElapsedTime();
        layerZero.update(duration);
        ImGui::SFML::Update(window, deltaClock.restart());


        window.clear(sf::Color::Black);
        window.draw(layerZero);
        window.draw(layerOne);
        window.draw(layerTwo);
        window.draw(button1);
        ImGui::SFML::Render(window);
        window.display();

    }
    ImGui::SFML::Shutdown();
    return 0;
}