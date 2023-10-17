//
// Created by alpacox on 14/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_HEROGUI_H
#define DRAGHI_E_SOTTERRANEI_HEROGUI_H

#include "HeroTabs.h"

class Hero;

class HeroGUI {
public:
    HeroGUI(Hero* hero, sf::VideoMode& vm);
    virtual ~HeroGUI();

    void toggleCharacterTab();

    void updateLevelBar();
    void updateEXPBar();
    void updateHPBar();
    void updateHeroTabs();
    void update(const float& dt);

    void renderLevelBar(sf::RenderTarget &target);
    void renderEXPBar(sf::RenderTarget &target);
    void renderHPBar(sf::RenderTarget &target);
    void renderHeroTabs(sf::RenderTarget &target);
    void render(sf::RenderTarget& target);

private:
    Hero* hero;

    sf::VideoMode& vm;
    sf::Font font;

    gui::ProgressBar* expBar;
    gui::ProgressBar* hpBar;

    std::string levelBarString;
    sf::Text levelBarText;
    sf::RectangleShape levelBarBack;

    HeroTabs* heroTabs;

    void initFont();
    void initHPBar();
    void initEXPBar();
    void initHeroTabs(sf::VideoMode& vm, sf::Font &font, Hero& hero);
    void initLevelBar();

};


#endif //DRAGHI_E_SOTTERRANEI_HEROGUI_H
