//
// Created by gabriele on 25/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_SWORD_H
#define DRAGHI_E_SOTTERRANEI_SWORD_H

#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword : public MeleeWeapon {
public:
    Sword(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range,
          unsigned value,
          std::string texture_file);
    ~Sword() override;

    void update(const sf::Vector2f& mouse_pos_view,  sf::Vector2f center) override;
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) override;

    Sword* clone() override;

};


#endif //DRAGHI_E_SOTTERRANEI_SWORD_H
