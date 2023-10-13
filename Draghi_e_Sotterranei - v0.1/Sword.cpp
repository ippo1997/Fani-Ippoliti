//
// Created by gabriele on 25/11/21.
//

#include "precompiler.h"
#include "Sword.h"

Sword::Sword(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range,
             unsigned value,
             std::string texture_file)
:MeleeWeapon(level, damageMin, damageMax, range, value, texture_file){
    //visualizzazione mirino
    weapon_sprite.setOrigin(
            weapon_sprite.getGlobalBounds().width / 2.f,
            weapon_sprite.getGlobalBounds().height
    );
}

Sword::~Sword() {

}

void Sword::update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f center) {

    //Update immagine mirino
    weapon_sprite.setPosition(center);
    float dX = mouse_pos_view.x - weapon_sprite.getPosition().x;
    float dY = mouse_pos_view.y - weapon_sprite.getPosition().y;

    const float PI = 3.14159265f;
    float deg = atan2(dY, dX) * 180.f / PI;

    weapon_sprite.setRotation(deg + 90.f);
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader) {
    if(shader)
        target.draw(weapon_sprite, shader);
    else
        target.draw(weapon_sprite);
}

Sword *Sword::clone() {
    return new Sword(*this);
}


