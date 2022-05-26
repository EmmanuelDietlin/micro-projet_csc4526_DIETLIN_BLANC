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

const int w_height = 800;
const int w_width = 1000;



int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    sf::Clock deltaClock;
    float color[4] = { 1.0f,1.0f,1.0f,1.0f };
    int figure = 0;
    float move[2] = { 0,0 };
    bool move_unique = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());
    }
    ImGui::SFML::Shutdown();
    return 0;
}