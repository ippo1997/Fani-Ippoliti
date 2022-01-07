//
// Created by gabriele on 25/11/21.
//

#include "precompiler.h"
#include "Bow.h"

Bow::Bow(unsigned level, unsigned value, std::string texture_file)
: RangedWeapon(level, value, texture_file){
}

Bow::~Bow() {

}

Bow *Bow::clone() {
    return new Bow(*this);
}

void Bow::update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f center) {

}

void Bow::render(sf::RenderTarget &target, sf::Shader *shader) {

}
