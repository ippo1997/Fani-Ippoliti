//
// Created by alpacox on 05/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_GAMECHARACTER_H
#define DRAGHI_E_SOTTERRANEI_GAMECHARACTER_H

#include "Weapon.h"
#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;
class SkillComponent;

class GameCharacter {
public:
    GameCharacter();
    virtual ~GameCharacter();

    void setTexture(sf::Texture& texture);
    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    void createMovementComponent(float maxVelocity,  float acceleration,  float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);
    void createAttributeComponent(unsigned level);
    void createSkillComponent();

    virtual AttributeComponent* getAttributeComponent();

    virtual const sf::Vector2f& getPosition() const;
    virtual sf::Vector2f getCenter() const;
    virtual sf::Vector2f getSpriteCenter() const;

    virtual sf::FloatRect getGlobalBounds() const;
    virtual sf::Vector2i getGridPosition(int gridSizeI) const;
    virtual sf::FloatRect getNextPositionBounds(const float& dt) const;

    virtual void setPosition(float x,  float y);

    virtual void move(float x,  float y, const float& dt);

    virtual bool isMovingX(){ return movingX;}
    virtual bool isMovingY(){ return movingY;}
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    float getSpriteDistance(const GameCharacter& gameCharacter) const;

    virtual void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader,  sf::Vector2f light_position,  bool show_hitbox) = 0;

protected:
    sf::Sprite sprite;

    HitboxComponent* hitboxComponent;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
    AttributeComponent* attributeComponent;
    SkillComponent* skillComponent;

    bool movingX = true;
    bool movingY = true;

private:
    void initVariables();

};

#endif //DRAGHI_E_SOTTERRANEI_GAMECHARACTER_H