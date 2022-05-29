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
#include "Fa�ade.h"


const int w_height = 800;
const int w_width = 1000;



int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    ImGui::SFML::Init(window);
    sf::Clock globalClock;
    sf::Clock deltaClock;

    Fa�ade fa�ade;

    tmx::Map map;
    map.load("resources/game_background.tmx");

    MapLayer layerBackground(map, 0);
    MapLayer layerBoat(map, 1);
    MapLayer layerForeground(map, 2);
    MapLayer layerGui1(map, 3);
    MapLayer layerGui2(map, 4);

    sf::RectangleShape fishMinus(sf::Vector2f(50, 25));
    fishMinus.setFillColor(sf::Color::Transparent);
    sf::RectangleShape fishPlus(sf::Vector2f(50, 25));
    fishPlus.setFillColor(sf::Color::Transparent);
    sf::RectangleShape rowMinus(sf::Vector2f(50, 25));
    rowMinus.setFillColor(sf::Color::Transparent);
    sf::RectangleShape rowPlus(sf::Vector2f(50, 25));
    rowPlus.setFillColor(sf::Color::Transparent);

    fishMinus.setPosition(115, 305);
    rowMinus.setPosition(115, 403);
    fishPlus.setPosition(322, 305);
    rowPlus.setPosition(322, 403);

    int tokenNbr = fa�ade.getTokenNbr();
    sf::Text counter;
    sf::Font font;
    font.loadFromFile("Montserrat-Regular.ttf");
    counter.setFont(font);
    counter.setString(std::to_string(tokenNbr));
    counter.setCharacterSize(50);
    counter.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (fishMinus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Tokens for fishing : " << fa�ade.removeTokenToFishing() << std::endl;
                } else if (fishPlus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Tokens for fishing : " << fa�ade.addTokenToFishing() << std::endl;
                } else if (rowMinus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Tokens for rowing : " << fa�ade.removeTokenToRowing() << std::endl;
                } else if (rowPlus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Tokens for rowing : " << fa�ade.addTokenToRowing() << std::endl;
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

        window.draw(counter);

        ImGui::SFML::Render(window);
        window.display();

    }
    ImGui::SFML::Shutdown();
    return 0;
}