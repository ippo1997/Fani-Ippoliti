//
// Created by alpacox on 09/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_HEROTABS_H
#define DRAGHI_E_SOTTERRANEI_HEROTABS_H

#include "CharacterTab.h"

enum class Hero_Tabs {CHARACTER_TAB = 0};

class HeroTabs {
public:
    HeroTabs(sf::VideoMode& vm,sf::Font& font, Hero& hero);
    virtual ~HeroTabs();

    bool getKeyTime();

    void toggleTab(const int tab_index);

    void update();
    void render(sf::RenderTarget& target);

private:
    std::vector<Tab*> tabs;

    sf::VideoMode& vm;
    sf::Font& font;
    Hero& hero;
    sf::Clock keyTimer;
    float keyTimeMax;

    void initTabs();
    void initKeyTime();

};


#endif //DRAGHI_E_SOTTERRANEI_HEROTABS_H
