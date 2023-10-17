//
// Created by alpacox on 05/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_WEAPON_H
#define DRAGHI_E_SOTTERRANEI_WEAPON_H

#include "Item.h"

class Item;

class Weapon : public Item {
public:
    Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range,
           unsigned value,
           std::string texture_file);
    ~Weapon() override;

    Item* clone() override = 0;
    virtual void generate( unsigned levelMin,  unsigned levelMax) = 0;

    virtual void update(const sf::Vector2f& mouse_pos_view,  sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;

    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const unsigned& getRange() const;
    bool getAttackTimer();

protected:
    sf::Texture weapon_texture;
    sf::Sprite weapon_sprite;

    unsigned damageMin;
    unsigned damageMax;
    unsigned range;

    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

private:
    void initVariables();

};

#endif //DRAGHI_E_SOTTERRANEI_WEAPON_H
