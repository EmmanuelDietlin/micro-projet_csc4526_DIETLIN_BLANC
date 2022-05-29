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

    Façade façade;

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

    int tokenNbr = façade.getTokenNbr();
    int fishingTokens = 0;
    int rowingTokens = 0;

    sf::Text counter;
    sf::Text fishingText;
    sf::Text rowingText;
    sf::Font font;

    font.loadFromFile("resources/Montserrat-Regular.otf");

    counter.setFont(font);
    counter.setString(std::to_string(tokenNbr)+" tokens left");
    counter.setCharacterSize(30);
    counter.setFillColor(sf::Color::Black);
    counter.setPosition(140, 200);

    fishingText.setFont(font);
    fishingText.setString("Fishing : " + std::to_string(fishingTokens) + " tokens");
    fishingText.setCharacterSize(15);
    fishingText.setFillColor(sf::Color::Black);
    fishingText.setPosition(200, 310);

    rowingText.setFont(font);
    rowingText.setString("Rowing : " + std::to_string(rowingTokens) + " tokens");
    rowingText.setCharacterSize(15);
    rowingText.setFillColor(sf::Color::Black);
    rowingText.setPosition(200, 405);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (fishMinus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Tokens for fishing : " << façade.removeTokenToFishing() << std::endl;
                } else if (fishPlus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Tokens for fishing : " << façade.addTokenToFishing() << std::endl;
                } else if (rowMinus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Tokens for rowing : " << façade.removeTokenToRowing() << std::endl;
                } else if (rowPlus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    std::cout << "Tokens for rowing : " << façade.addTokenToRowing() << std::endl;
                }
            }
        }
        tokenNbr = façade.getTokenNbr();
        fishingTokens = façade.getFishingTokens();
        rowingTokens = façade.getRowingTokens();

        counter.setString(std::to_string(tokenNbr) + " tokens left");
        fishingText.setString("Fishing : \n" + std::to_string(fishingTokens) + " tokens");
        rowingText.setString("Rowing : \n" + std::to_string(rowingTokens) + " tokens");

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
        window.draw(fishingText);
        window.draw(rowingText);

        ImGui::SFML::Render(window);
        window.display();

    }
    ImGui::SFML::Shutdown();
    return 0;
}