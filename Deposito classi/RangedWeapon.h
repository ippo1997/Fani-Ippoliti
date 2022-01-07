//
// Created by gabriele on 25/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_RANGEDWEAPON_H
#define DRAGHI_E_SOTTERRANEI_RANGEDWEAPON_H

#include "Weapon.h"

class RangedWeapon : public Weapon {
public:
    RangedWeapon(unsigned level, unsigned value, std::string texture_file);
    virtual ~RangedWeapon();

    virtual RangedWeapon* clone() = 0;
    void generate(const unsigned levelMin, const unsigned levelMax) override;

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;

};


#endif //DRAGHI_E_SOTTERRANEI_RANGEDWEAPON_H
