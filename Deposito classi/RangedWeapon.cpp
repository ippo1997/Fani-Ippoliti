//
// Created by gabriele on 25/11/21.
//

#include "precompiler.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned level, unsigned value, std::string texture_file)
: Weapon(level, value, texture_file) {
    type = ItemTypes::ITEM_RANGEDWEAPON;
}

RangedWeapon::~RangedWeapon() {

}

void RangedWeapon::generate(const unsigned int levelMin, const unsigned int levelMax) {

}
