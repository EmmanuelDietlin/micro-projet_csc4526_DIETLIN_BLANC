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
#include <memory>
#include "SFMLOrthogonalLayer.h"
#include "signals.h"

const int w_height = 800;
const int w_width = 1000;
const int maxDay = 47;
const int maxDistance = 6700;
const int playerBaseHp = 100;
const int boatBaseHp = 200;
const int spacing = 10;
const int baseMaterialNbr = 10;
const int sleep_delay = 17; //nbr de ms pour avoir 60FPS

/// <summary>
/// Choisit un entier al�atoirement entre deux entiers, selon une distribution uniforme
/// </summary>
/// <param name="start"> entier de d�part </param>
/// <param name="end">entier de fin</param>
/// <returns> entier choisi</returns>
int random_int(int const start, int const end) {
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_int_distribution<> distribution(start, end);
    return distribution(engine);
}

/// <summary>
/// Cr�� un texte ImGui centr� sur la page ImGui.
/// </summary>
/// <param name="s"> chaine de charact�res pour le texte </param>
void TextCentered(std::string const& s) {
    auto textWidth = ImGui::CalcTextSize(s.c_str()).x;
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - textWidth) * 0.5f);
    ImGui::Text(s.c_str());
}

/// <summary>
/// Calcule le nombre de jetons restants.
/// Emp�che de consommer plus de jetons que disponibles.
/// La m�thode est � utiliser � chaque fois qu'on modifie le nombre d'un type de jetons dans la map des jetons
/// </summary>
/// <param name="t"> map des jetons </param>
/// <param name="type"> type des jetons qu'on ajoute </param>
void RemainingTokens(std::map<TokensType, int>& t, TokensType const& type) {
    int r;
    r = t[TokensType::tokenNbr];
    for (auto it : t) {
        if (it.first != TokensType::tokenNbr && it.first != TokensType::remainingTokens) {
            r -= it.second;
        }
    }
    if (t[type] < 0) {
        r += t[type];
        t[type] = 0;
    }
    if (r < 0) {
        t[type] += r;
        r = 0;
    }
    t[TokensType::remainingTokens] = r;
}

/// <summary>
/// Ajoute un espacement de taille "spacing" entre deux �l�ments ImGui.
/// </summary>
void ImGuiYSpacing() {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing);
}

/// <summary>
/// D�clenchement le fondu au noir.
/// </summary>
/// <param name="f"> compteur pour le fondu </param>
void FadeToBlack(int& f) {
    f = 0;
}
/// <summary>
/// G�n�re une fen�tre ImGui couvant toute la taille de la fen�tre, avec un titre et un bouton.
/// V�rifie �galement si le bouton est press�
/// </summary>
/// <param name="title"> Titre de la fen�tre </param>
/// <param name="txt1"> Ligne 1 du texte de la page </param>
/// <param name="txt2"> Ligne 2 du texte de la page </param>
/// <param name="b_label"> Texte du bouton </param>
/// <returns> vrai si le bouton est press� </returns>
bool SetMenuWindow(std::string const& title, std::string const& txt1, std::string const& txt2,
	std::string const& b_label) {
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0.5f, 0.5f));
	ImGui::SetNextWindowPos(sf::Vector2f(0, 0));
	ImGui::SetNextWindowSize(sf::Vector2f(w_width, w_height));
	ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

	ImGui::SetCursorPosY(w_height * 0.1f);
	ImGui::SetWindowFontScale(5);
	TextCentered(txt1);
	TextCentered(txt2);
	ImGui::SetWindowFontScale(1.3f);
	ImGui::SetCursorPos(sf::Vector2f(w_width / 2 - 100, w_height / 2 - 100));
	if (ImGui::Button(b_label.c_str(), sf::Vector2f(200, 100))) {
		return true;
	}

	return false;
}

/// <summary>
/// Lis le contenu du fichier "recap.txt", regroupant le compte rendu des actions et �v�nements 
/// d'une journ�e
/// </summary>
/// <param name="s"> conteneur du texte lu dans le fichier </param>
void readRecap(std::stringstream& s) {
    s.str(std::string());   
    std::ifstream recapFile("resources/recap.txt");
    s << recapFile.rdbuf();
    recapFile.close();
}

/// <summary>
/// Remet � z�ro la r�partition des jetons d'action dans la map.
/// </summary>
/// <param name="t"> map des jetons</param>
void resetTokens(std::map<TokensType, int>& t) {
    for (auto it = t.begin(); it != t.end(); it++) {
        if (it->first != TokensType::tokenNbr && it->first != TokensType::remainingTokens)
            it->second = 0;
    }
    t[TokensType::remainingTokens] = t[TokensType::tokenNbr];
}





int myMain()
{
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "SFML ");
    ImGui::SFML::Init(window);
    sf::Clock globalClock;
    sf::Clock deltaClock;
    sf::Clock faderClock;
    
    

    auto imguiWindow = ImGuiWindow::mainMenu;

    std::stringstream recapText;
    bool upgradeFishing = false;
    bool upgradeRowing = false;

    std::stringstream infos;
    std::ifstream infoFile("resources/readme.txt");
    infos << infoFile.rdbuf();
    infoFile.close();

    int random_bg = random_int(0, 100);

    std::unique_ptr<Fa�ade> fa�ade;
    int fade_counter = 256;
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
    player.setPosition(sf::Vector2f(720, 390));
    player.setTexture(&playerTexture);

    auto spriteClock = globalClock.getElapsedTime();

    tmx::Map map;
    map.load("resources/game_background.tmx");

    MapLayer layerBackground(map, 0);
    MapLayer layerBoat(map, 1);
    MapLayer layerForeground(map, 2);
    MapLayer layerRowingUpgrade(map, 4);
    MapLayer layerFishingUpgrade(map, 5);
    MapLayer layerFarBoat(map, 6);
    MapLayer layerFarIslands(map, 7);

    std::map<TokensType, int> tokens;
    tokens[TokensType::tokenNbr] = 0;
    tokens[TokensType::fishingsTokens] = 0;
    tokens[TokensType::rowingTokens] = 0;
    tokens[TokensType::healingTokens] = 0;
    tokens[TokensType::repairTokens] = 0;
    tokens[TokensType::remainingTokens] = 0;
    tokens[TokensType::upgradeFishingToken] = 0;
    tokens[TokensType::upgradeRowingToken] = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (imguiWindow != ImGuiWindow::mainMenu) {
                FadeToBlack(fade_counter);
                imguiWindow = ImGuiWindow::mainMenu;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        if (imguiWindow == ImGuiWindow::mainMenu) {
            if (SetMenuWindow("Main menu", "Les revoltes", "de la Bounty",
                "Commencer la partie")) {
                FadeToBlack(fade_counter);
                fa�ade = std::make_unique<Fa�ade>(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterialNbr);
                tokens[TokensType::tokenNbr] = fa�ade->getTokenNbr();
                tokens[TokensType::remainingTokens] = fa�ade->getTokenNbr();
                readRecap(recapText);
                imguiWindow = ImGuiWindow::gameWindow1;
            }
            ImGuiYSpacing();
            ImGui::SetCursorPosX(w_width / 2 - 100);
            if (fa�ade) {
                if (ImGui::Button("Continuer la partie", sf::Vector2f(200, 100))) {
                    FadeToBlack(fade_counter);
                    imguiWindow = ImGuiWindow::gameWindow1;
                }
            }
            ImGuiYSpacing();
            ImGui::SetCursorPosX(w_width / 2 - 100);
            if (ImGui::Button("Informations", sf::Vector2f(200, 100))) {
                FadeToBlack(fade_counter);
                imguiWindow = ImGuiWindow::informations;
            }
            ImGuiYSpacing();
            ImGui::SetCursorPosX(w_width / 2 - 100);
            if (ImGui::Button("Quitter le jeu", sf::Vector2f(200, 100))) {
                window.close();
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
            ImGui::SetWindowFontScale(3);
            TextCentered("Jour " + std::to_string(fa�ade->getDayCount()));
            ImGui::SetWindowFontScale(1.3f);
            ImGuiYSpacing();

			if (imguiWindow == ImGuiWindow::gameWindow1) {
				ImGui::TextWrapped(recapText.str().c_str());
				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
				if (ImGui::Button("Page suivante")) {
					imguiWindow = ImGuiWindow::gameWindow2;
				}
			}
			else if (imguiWindow == ImGuiWindow::gameWindow2) {
				ImGui::Text("Distance parcourue : %d km", fa�ade->getDistanceTravelled());
				ImGui::ProgressBar((float)fa�ade->getDistanceTravelled() / (float)maxDistance);
				ImGuiYSpacing();
				ImGui::Text("Jetons restants : %d", tokens[TokensType::remainingTokens]);
				if (ImGui::InputInt("Pecher", &tokens[TokensType::fishingsTokens], 1)) {
					RemainingTokens(tokens, TokensType::fishingsTokens);
				}
				if (ImGui::InputInt("Ramer", &tokens[TokensType::rowingTokens], 1)) {
					RemainingTokens(tokens, TokensType::rowingTokens);
				}
				if (ImGui::InputInt("Se soigner", &tokens[TokensType::healingTokens], 1)) {
					RemainingTokens(tokens, TokensType::healingTokens);
				}
				if (ImGui::InputInt("Reparer", &tokens[TokensType::repairTokens], 1)) {
					RemainingTokens(tokens, TokensType::repairTokens);
				}
				ImGuiYSpacing();
				ImGui::Text("Poissons : %d", fa�ade->getFishCount());
                ImGuiYSpacing();
                ImGui::Text("Materiaux : %d", fa�ade->getMaterials());
                ImGuiYSpacing();
                float cursor_y = ImGui::GetCursorPosY();
                if (ImGui::Checkbox("Ameliorer peche", &upgradeFishing)) {
                    if ((upgradeRowing && fa�ade->getMaterials() - rod_materials_required - boat_materials_required < 0) ||
                        (!upgradeRowing && fa�ade->getMaterials() < rod_materials_required) || (tokens[TokensType::remainingTokens] == 0)) {
                        upgradeFishing = false;
                    }
                    upgradeFishing ? tokens[TokensType::upgradeFishingToken] = 1 : tokens[TokensType::upgradeFishingToken] = 0;
                    RemainingTokens(tokens, TokensType::upgradeFishingToken);
                }
                ImGui::Text("%d materiaux + \n1 jeton", rod_materials_required);
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f);
                ImGui::SetCursorPosY(cursor_y);
                if (ImGui::Checkbox("Ameliorer bateau", &upgradeRowing)) {
                    if ((upgradeFishing && fa�ade->getMaterials() - rod_materials_required - boat_materials_required < 0) ||
                        (!upgradeFishing && fa�ade->getMaterials() < boat_materials_required) || (tokens[TokensType::remainingTokens] == 0)) {
                        upgradeRowing = false;
                    }
                    upgradeRowing ? tokens[TokensType::upgradeRowingToken] = 1 : tokens[TokensType::upgradeRowingToken] = 0;
                    RemainingTokens(tokens, TokensType::upgradeRowingToken);
                }
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f);
                ImGui::Text("%d materiaux + \n1 jeton", boat_materials_required);

				ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 160) * 0.5f);
				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 180);
				if (ImGui::Button("Jour suivant", ImVec2(160, 90))) {
                    std::cout << "upgradeRowing : " << tokens[TokensType::upgradeRowingToken] << std::endl;
                    std::cout << "upgradeFishing : " << tokens[TokensType::upgradeFishingToken] << std::endl;
					FadeToBlack(fade_counter);
                    auto ret = fa�ade->nextDay(tokens);
					readRecap(recapText);
                    resetTokens(tokens);
                    upgradeFishing = false;
                    upgradeRowing = false;
                    random_bg = random_int(0, 100);
                    if (ret == Status::onGoing)
                        imguiWindow = ImGuiWindow::gameWindow1;
                    else if (ret == Status::victory)
                        imguiWindow = ImGuiWindow::victory;
                    else if (ret == Status::defeat)
                        imguiWindow = ImGuiWindow::defeat;
				}
				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
				if (ImGui::Button("Page precedente")) {
					imguiWindow = ImGuiWindow::gameWindow1;
				}
			}
			ImGui::PopStyleColor(1);
			ImGui::End();


            ImGui::SetNextWindowPos(sf::Vector2f(650, 290));
            ImGui::SetNextWindowSize(sf::Vector2f(150, 100));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5f));

            ImGui::Begin("Player", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            ImGui::Text("Pv joueur");
            ImGui::ProgressBar((float)fa�ade->getPlayerHp() / (float)playerBaseHp);
            ImGui::Text("Pv bateau");
            ImGui::ProgressBar((float)fa�ade->getBoatHp() / (float)boatBaseHp);
            ImGui::End();
            ImGui::PopStyleColor(1);


            
            if (globalClock.getElapsedTime() - spriteClock > sf::seconds(0.5f)) {
                spriteClock = globalClock.getElapsedTime();
                spriteIndex = (spriteIndex + 1) % 4;
                playerTexture.loadFromImage(sprites[spriteIndex]);
            }
            window.clear(sf::Color::Black);
            window.draw(layerBackground);
            window.draw(layerBoat);
            window.draw(layerForeground);
            if (fa�ade->getFishingUpgradeStatus()) window.draw(layerFishingUpgrade);
            if (fa�ade->getRowingUpgradeStatus()) window.draw(layerRowingUpgrade);

            if (random_bg < 10) {
                window.draw(layerFarBoat);
            }
            else if (random_bg < 20) {
                window.draw(layerFarIslands);
            }
            else if (random_bg < 30) {
                window.draw(layerFarBoat);
                window.draw(layerFarIslands);
            }
            window.draw(player);

            ImGui::SFML::Render(window);
        }
        else if (imguiWindow == ImGuiWindow::victory) {
            if (SetMenuWindow("Victory screen", "Vous avez", "gagne !",
                "Retour au menu")) {
                FadeToBlack(fade_counter);
                fa�ade.reset();
                imguiWindow = ImGuiWindow::mainMenu;
            }
            ImGui::End();
            ImGui::PopStyleColor(2);
            ImGui::SFML::Render(window);
        }
        else if (imguiWindow == ImGuiWindow::defeat) {
            if (SetMenuWindow("Defeat screen", "Vous avez", "perdu !",
                "Retour au menu")) {
                FadeToBlack(fade_counter);
                fa�ade.reset();
                imguiWindow = ImGuiWindow::mainMenu;
            }
            ImGui::End();
            ImGui::PopStyleColor(2);
            ImGui::SFML::Render(window);
        }
        else if (imguiWindow == ImGuiWindow::informations) {
            ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0.5f, 0.5f));
            ImGui::SetNextWindowPos(sf::Vector2f(0, 0));
            ImGui::SetNextWindowSize(sf::Vector2f(w_width, w_height));
            ImGui::Begin("Informations", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

            ImGui::SetCursorPosY(w_height * 0.1f);
            ImGui::SetWindowFontScale(5);
            ImGuiYSpacing();
            TextCentered("Informations");
            ImGui::SetWindowFontScale(1.3f);
            ImGuiYSpacing();
            ImGui::TextWrapped(infos.str().c_str());
            ImGuiYSpacing();
            ImGui::SetCursorPos(sf::Vector2f(w_width / 2 - 100, ImGui::GetWindowHeight() - 200));
            if (ImGui::Button("Retour au menu", sf::Vector2f(200, 100))) {
                FadeToBlack(fade_counter);
                imguiWindow = ImGuiWindow::mainMenu;
            }
            ImGui::End();
            ImGui::PopStyleColor(2);
            ImGui::SFML::Render(window);
        }

        if (faderClock.getElapsedTime() > sf::seconds(0.005f) && fade_counter < 256) {
            fader.setFillColor(sf::Color(0, 0, 0, 255-fade_counter));
            fade_counter+=6;
            faderClock.restart();
        }

        window.draw(fader);
        window.display();
        Sleep(sleep_delay); //On limite la vitesse du jeu � maximum 60FPS
    }
    ImGui::SFML::Shutdown();
    return 0;
}
