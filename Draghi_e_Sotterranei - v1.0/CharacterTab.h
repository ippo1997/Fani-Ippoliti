//
// Created by alpacox on 09/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_CHARACTERTAB_H
#define DRAGHI_E_SOTTERRANEI_CHARACTERTAB_H

#include "Tab.h"

class CharacterTab : public Tab{
public:
    CharacterTab(sf::VideoMode& vm, sf::Font& font, Hero& hero);
    ~CharacterTab() override;

    void update() override;
    void render(sf::RenderTarget& target) override;

private:
    sf::RectangleShape back;
    sf::Text infoText;

    void initText();
};


#endif //DRAGHI_E_SOTTERRANEI_CHARACTERTAB_H
