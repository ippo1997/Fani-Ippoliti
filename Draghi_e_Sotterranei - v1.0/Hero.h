//
// Created by alpacox on 05/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_HERO_H
#define DRAGHI_E_SOTTERRANEI_HERO_H

#include "GameCharacter.h"
#include "Items.h"

class  GameCharacter;

class Hero : public GameCharacter {
public:
    Hero(float x, float y, sf::Texture& texture_sheet);
    virtual ~Hero();

    AttributeComponent* getAttributeComponent();
    Weapon* getWeapon() const;

    const std::string toStringCharacterTab() const;
    const bool& getInitAttack() const;

    void setInitAttack(bool initAttack);

    bool getDamageTimer();

    unsigned getDamage() const;
    virtual bool isDead() const;

    void loseHP(int hp);
    void gainEXP(int exp);
    void updateAttack();
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view) override;
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, sf::Vector2f light_position = sf::Vector2f() , bool show_hitbox = false) override;


private:
    bool initAttack;
    bool attacking;
    Weapon* weapon;

    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;

    void initVariables();
    void initAnimations();

};


#endif //DRAGHI_E_SOTTERRANEI_HERO_H
