//
// Created by alpacox on 08/10/21.
//

#include "precompiler.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font, PauseTypes type)
: font(font){
    background.setSize(sf::Vector2f(
            static_cast<float >(vm.width),
            static_cast<float >(vm.height)
               )
            );
    background.setFillColor(sf::Color(20, 20, 20, 100));

    container.setSize(sf::Vector2f(
            static_cast<float >(vm.width) / 4.f,
            static_cast<float >(vm.height) - gui::p2pY(41.6f, vm)
               )
            );
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(
            static_cast<float >(vm.width) / 2.f - container.getSize().x /2.f,
            150.f
            );
    menuText.setFont(font);
    menuText.setCharacterSize(gui::calcCharSize(vm));

    if(type == PauseTypes::PAUSE_STATE){
        menuText.setFillColor(sf::Color(255, 255, 255, 200));
        menuText.setString("PAUSED");
    }
    else if(type == PauseTypes::GAME_OVER_STATE){
        menuText.setFillColor(sf::Color(255, 0, 0, 200));
        menuText.setString("GAME OVER");
    }
    else if(type == PauseTypes::WINNING_STATE){
        menuText.setFillColor(sf::Color(0, 255, 0, 200));
        menuText.setString("YOU WIN");
    }

    menuText.setPosition(container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f,
                               container.getPosition().y + gui::p2pY(3.f,vm));
}

PauseMenu::~PauseMenu() {
    auto i = buttons.begin();
    for (i = buttons.begin(); i != buttons.end(); ++i){
        delete i->second;
    }
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow) {
    for(auto &i : buttons){
        i.second->update(mousePosWindow);
    }
}

void PauseMenu::render(sf::RenderTarget &target) {
    target.draw(background);
    target.draw(container);

    for(auto &i : buttons)
        i.second->render(target);

    target.draw(menuText);
}

void PauseMenu::addButton(std::string key, float y, float width, float height, unsigned char_size, std::string text) {
    float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
    buttons[key] = new gui::Button(
            x, y, width, height,
            &font, text, char_size,
            sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

bool PauseMenu::isButtonPressed(std::string key){
    return buttons[key]->isPressed();
}

