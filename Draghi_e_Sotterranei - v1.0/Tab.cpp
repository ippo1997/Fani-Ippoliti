//
// Created by alpacox on 09/12/21.
//

#include "precompiler.h"
#include "Tab.h"

Tab::Tab(sf::VideoMode& vm, sf::Font& font, Hero& hero, bool hidden)
: vm(vm), font(font), hero(hero), hidden(hidden) {

}

Tab::~Tab() {

}

const bool &Tab::getOpen() const {
    return hidden;
}

void Tab::show() {
    hidden = false;
}

void Tab::toggle() {
    if(hidden)
        hidden = false;
    else
        hidden = true;
}