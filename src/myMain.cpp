#include "myMain.h"
#include <iostream>
#include <vector>
#include "Group.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <Windows.h>
#include <thread>
#include <imgui.h>
#include <imgui-SFML.h>

const int w_height = 800;
const int w_width = 1000;


void printAsText(std::vector<std::pair<std::string, std::string>>& m, Group& g) {
    m.clear();
    g.printAsText(w_width / 2, w_height / 2, m);
    for (auto i = 0; i < m.size(); i++) {
        std::cout << "#" << i << " " << m[i].second;
    }
}

void printAsImage(Group& g, sf::RenderWindow& w) {
    g.draw(w_width/2, w_height/2, w);
}

void modifyDrawing(Group *g) {
    std::vector<Shape*> v;
    g->getShapes(v);
    std::string f;
    std::string a;
    int figure;
    int action;
    while (true) {
        std::cout << "Rank of object to modify ? (type exit to leave)" << std::endl;
        while (!(std::cin >> f) || f == "\n") {}
        if (f == "exit") { exit(0); }
        try {
            figure = stoi(f);
        }
        catch (std::invalid_argument) {
            std::cout << "Action could not be determined, returning to figure selection " << std::endl;
            goto out;
        }

            std::cout << "Modify object " << figure << std::endl;
            std::cout << "1: Change color" << std::endl;
            std::cout << "2: Copy" << std::endl;
            std::cout << "3: Translation by (delta_x, delta_y)" << std::endl;
            std::cin >> a;
            try {
                action = stoi(a);
            }
            catch (std::invalid_argument) {
                std::cout << "Action could not be determined, returning to figure selection " << std::endl;
                goto out;
            }
            if (action == 1) {
                std::cout << "1 : Black" << std::endl;
                std::cout << "2 : White" << std::endl;
                std::cout << "3 : Red" << std::endl;
                std::cout << "4 : Magenta" << std::endl;
                std::cout << "5 : Blue" << std::endl;
                int color;
                std::string c;
                std::cin >> c;
                try {
                    color = stoi(c);
                }
                catch (std::invalid_argument) {
                    std::cout << "Action could not be determined, returning to figure selection " << std::endl;
                    goto out;
                }

                if (color == 1) c = "Black";
                else if (color == 2) c = "White";
                else if (color == 3) c = "Red";
                else if (color == 4) c = "Magenta";
                else if (color == 5) c = "Blue";
                else c = "Black";
               (*g).changeColor(c, v[figure]->getId());
            }
            else if (action == 2) {
            }
            else if (action == 3) {
                std::cout << "Enter translation delta : delta_x delta_y" << std::endl;
                float dx, dy;
                std::cin >> dx >> dy;
                v[figure]->move(dx, dy, v[figure]->getId());
                std::cout << "Object successfully moved" << std::endl;
            }
            else {
                std::cout << "Action could not be determined, returning to figure selection " << std::endl;
                goto out;
            }

    out:
        std::cout << "" << std::endl;
    }
    
}


int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("resources/visage.xml");
    ImGui::SFML::Init(window);
    if (!result) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }
    pugi::xml_node b = doc.child("Drawing");
    Group g(b);
    std::vector<std::pair<std::string, std::string>> m;
    printAsText(m, g);
    window.clear(sf::Color::White);
    printAsImage(g, window);
    window.display();
    std::vector<Shape*> v;
    g.getShapes(v);
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

        ImGui::Begin("Modify the drawing");

        ImGui::SliderInt("Figure number to modify", &figure, 0, v.size() - 1);
        if (ImGui::CollapsingHeader("Change color")) {
            ImGui::ColorEdit3("color", color);
            std::string c;
            if (ImGui::Button("Black")) { 
                c = "Black"; 
                g.changeColor(c, v[figure]->getId());
                printAsText(m, g);
            }
            if (ImGui::Button("Blue")) {
                c = "Blue";
                g.changeColor(c, v[figure]->getId());
                printAsText(m, g);
            }
            if (ImGui::Button("Red")) {
                c = "Red";
                g.changeColor(c, v[figure]->getId());
                printAsText(m, g);
            }
            if (ImGui::Button("White")) {
                c = "White";
                g.changeColor(c, v[figure]->getId());
                printAsText(m, g);
            }
            if (ImGui::Button("Magenta")) {
                c = "Magenta";
                g.changeColor(c, v[figure]->getId());
                printAsText(m, g);
            }
            if (ImGui::Button("CustomColor")) {
                g.changeColor((int)(color[0]*255), (int)(color[1] * 255), (int)(color[2] * 255), v[figure]->getId());
                printAsText(m, g);
            }
        }
        ImGui::InputFloat("X delta", &move[0], 0, 0);
        ImGui::InputFloat("Y delta", &move[1], 0, 0);
        ImGui::Checkbox("Only move this instance of the object", &move_unique);
        if (ImGui::Button("Move")) {
            if (move_unique) {
                v[figure]->move(move[0], move[1], v[figure]->getId());
            }
            else {
                g.move(move[0], move[1], v[figure]->getId());
            }
        }
        if (ImGui::Button("Copy")) {
            auto s = v[figure]->copy();
            g.addShape(s);
            v.clear();
            g.getShapes(v);
            std::cout << "index = " << v.size() - 1 << std::endl;
            ImGui::Text("Object successfully copied !");
            printAsText(m, g);
        }
        ImGui::End();

        window.clear(sf::Color::White);
        g.draw(w_width / 2, w_height / 2, window);
        ImGui::SFML::Render(window);
        window.display();
        Sleep(30);


    }
    ImGui::SFML::Shutdown();
    return 0;
}