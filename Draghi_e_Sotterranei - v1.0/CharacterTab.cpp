//
// Created by alpacox on 09/12/21.
//

#include "precompiler.h"
#include "CharacterTab.h"

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, Hero& hero)
: Tab(vm, font, hero, true) {
    back.setFillColor(sf::Color(30, 30, 30, 200));
    back.setSize(sf::Vector2f(gui::p2pX(22.f, this->vm), gui::p2pX(20.f, this->vm)));
    back.setPosition(20, 150);

    initText();
}

CharacterTab::~CharacterTab() {

}

void CharacterTab::update() {
    if(!hidden)
        infoText.setString(hero.toStringCharacterTab());
}

void CharacterTab::render(sf::RenderTarget &target) {
    if(!hidden){
        target.draw(back);
        target.draw(infoText);
    }
}

void CharacterTab::initText() {
    infoText.setFont(font);
    infoText.setCharacterSize(gui::calcCharSize(vm, 100));
    infoText.setFillColor(sf::Color(200, 200, 200, 240));
    infoText.setPosition(back.getPosition().x + 20.f, back.getPosition().y + 20.f);
    infoText.setString(hero.toStringCharacterTab());
}


