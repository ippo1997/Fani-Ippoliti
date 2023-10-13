//
// Created by alpacox on 08/10/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_PAUSEMENU_H
#define DRAGHI_E_SOTTERRANEI_PAUSEMENU_H

#include "State.h"
#include "Gui.h"

enum class PauseTypes {PAUSE_STATE, GAME_OVER_STATE, WINNING_STATE};

class PauseMenu {
public:
    PauseMenu(sf::VideoMode& vm, sf::Font& font, PauseTypes type);
    virtual ~PauseMenu();

    bool isButtonPressed(std::string key);
    void addButton(std::string key, float y, float width, float height, unsigned char_size, std::string text);

    void update(const sf::Vector2i& mousePosWindow);
    void render(sf::RenderTarget& target);

private:
    sf::Font& font;
    sf::Text menuText;
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button*> buttons;

};


#endif //DRAGHI_E_SOTTERRANEI_PAUSEMENU_H
