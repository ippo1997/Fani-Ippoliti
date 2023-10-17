//
// Created by gabriele on 25/11/21.
//

#include "precompiler.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range,
                         unsigned value,
                         std::string texture_file)
: Weapon(level, damageMin, damageMax, range, value, texture_file) {
    type = ItemTypes::ITEM_MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon() {

}

void MeleeWeapon::generate(const unsigned int levelMin, const unsigned int levelMax) {

    level = rand() % (levelMax - levelMin + 1) + levelMin;

    damageMin = level * (rand() % 2 + 1);
    damageMax = level * (rand() % 2 + 1) + damageMin;

    range = level + rand() % 10 + 50;

    value = level + damageMin + damageMax + range + (rand() % level * 10);

    std::cout << level << " " << damageMin << " " << damageMax << " " << range << " " << value << "\n";
}
