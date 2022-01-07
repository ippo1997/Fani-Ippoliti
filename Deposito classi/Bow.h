//
// Created by gabriele on 25/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_BOW_H
#define DRAGHI_E_SOTTERRANEI_BOW_H

#include "RangedWeapon.h"

class RangedWeapon;

class Bow : public RangedWeapon {
public:
    Bow(unsigned level, unsigned value, std::string texture_file);
    virtual ~Bow();

    Bow* clone() override;

    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);

};

#endif //DRAGHI_E_SOTTERRANEI_BOW_H
