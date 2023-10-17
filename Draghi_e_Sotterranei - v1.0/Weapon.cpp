//
// Created by alpacox on 05/03/21.
//

#include "precompiler.h"
#include "Weapon.h"

Weapon::Weapon(unsigned level, unsigned int damageMin, unsigned int damageMax, unsigned int range,
               unsigned int value,
               std::string texture_file)
               : Item(level, value){

    initVariables();

    this->damageMin = damageMin;
    this->damageMax = damageMax;
    this->range = range;

    if(!weapon_texture.loadFromFile(texture_file))
        std::cout <<"ERROR::SWORD::COULD NOT LOAD WEAPON TEXTURE::"<< texture_file << "\n";
    weapon_sprite.setTexture(weapon_texture);
}

Weapon::~Weapon() {

}

void Weapon::initVariables() {
    range = 65;
    damageMin = 1;
    damageMax = 2;

    attackTimer.restart();
    attackTimerMax = 500;
}

const unsigned &Weapon::getDamageMin() const {
    return damageMin;
}

const unsigned &Weapon::getDamageMax() const {
    return damageMax;
}

const unsigned &Weapon::getRange() const {
    return range;
}

bool Weapon::getAttackTimer() {
    if(attackTimer.getElapsedTime().asMilliseconds() >= attackTimerMax){
        attackTimer.restart();
        return true;
    }
    return false;
}
