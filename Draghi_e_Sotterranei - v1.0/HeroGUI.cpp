//
// Created by alpacox on 14/11/21.
//

#include "precompiler.h"
#include "HeroGUI.h"

HeroGUI::HeroGUI(Hero* hero, sf::VideoMode& vm)
        : vm(vm){

    this->hero = hero;

    initFont();
    initLevelBar();
    initEXPBar();
    initHPBar();
    initHeroTabs(vm, font, *hero);
}

HeroGUI::~HeroGUI() {
    delete hpBar;
    delete expBar;
    delete heroTabs;
}

void HeroGUI::initFont() {
    font.loadFromFile("./Fonts/DeterminationMonoWebRegular-Z5oq.ttf");
}

void HeroGUI::initLevelBar() {
    float width = gui::p2pX(2.34f, this->vm);
    float height = gui::p2pY(4.16f, this->vm);
    float x = gui::p2pX(1.56f, this->vm);
    float y = gui::p2pY(2.77f, this->vm);

    levelBarBack.setSize(sf::Vector2f(width, height));
    levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    levelBarBack.setPosition(x, y);
    levelBarText.setFont(font);
    levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 75));
    levelBarText.setPosition(
            levelBarBack.getPosition().x + gui::p2pX(0.78f, this->vm),
            levelBarBack.getPosition().y - gui::p2pY(0.69f, this->vm)
            );
}

void HeroGUI::initEXPBar() {
    expBar = new gui::ProgressBar(1.56f, 6.94, 15.6f, 2.77f,
                                       hero->getAttributeComponent()->expNext,
                                        sf::Color(20, 20, 250, 200),
                                       this->vm, 100,
                                       &font);
}

void HeroGUI::initHPBar() {
    hpBar = new gui::ProgressBar(1.56f, 12.5f, 15.6f, 4.16f,
                                       hero->getAttributeComponent()->hpMax,
                                       sf::Color(250, 20, 20, 200),
                                       this->vm, 75,
                                       &font);
}

void HeroGUI::initHeroTabs(sf::VideoMode& vm, sf::Font &font, Hero& hero) {
    heroTabs = new HeroTabs(vm, font, hero);
}

void HeroGUI::updateLevelBar() {
    levelBarString = std::to_string(hero->getAttributeComponent()->level);
    levelBarText.setString(levelBarString);
}

void HeroGUI::updateEXPBar() {
    expBar->update(hero->getAttributeComponent()->exp);
}

void HeroGUI::updateHPBar() {
    hpBar->update(hero->getAttributeComponent()->hp);
}

void HeroGUI::updateHeroTabs() {
    heroTabs->update();
}

void HeroGUI::update(const float &dt) {
    updateLevelBar();
    updateEXPBar();
    updateHPBar();
    updateHeroTabs();
}

void HeroGUI::renderLevelBar(sf::RenderTarget &target) {
    target.draw(levelBarBack);
    target.draw(levelBarText);
}

void HeroGUI::renderEXPBar(sf::RenderTarget &target) {
    expBar->render(target);
}

void HeroGUI::renderHPBar(sf::RenderTarget &target) {
    hpBar->render(target);
}

void HeroGUI::renderHeroTabs(sf::RenderTarget &target) {
    heroTabs->render(target);
}

void HeroGUI::render(sf::RenderTarget &target) {
    renderLevelBar(target);
    renderEXPBar(target);
    renderHPBar(target);
    renderHeroTabs(target);
}

void HeroGUI::toggleCharacterTab() {
    heroTabs->toggleTab(static_cast<int>(Hero_Tabs::CHARACTER_TAB));
}
