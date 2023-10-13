//
// Created by alpacox on 05/10/21.
//

#include "precompiler.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite,
                                 float offset_x, float offset_y,
                                 float width, float height)
                                 : sprite(sprite), offsetX(offset_x), offsetY(offset_y){
    nextPosition.left = 0.f;
    nextPosition.top = 0.f;
    nextPosition.width = width;
    nextPosition.height = height;
    hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
    hitbox.setSize(sf::Vector2f(width, height));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(-1.f);
    hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent() {

}

void HitboxComponent::update() {
    hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitboxComponent::render(sf::RenderTarget &target) {
    target.draw((hitbox));
}

bool HitboxComponent::intersect(const sf::FloatRect& frect) {
    return hitbox.getGlobalBounds().intersects(frect);
}

const sf::Vector2f &HitboxComponent::getPosition() const {
    return hitbox.getPosition();
}

void HitboxComponent::setPosition(const sf::Vector2f& position) {
    hitbox.setPosition(position);
    sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void HitboxComponent::setPosition(const float x, const float y) {
    hitbox.setPosition(x, y);
    sprite.setPosition(x - offsetX, y - offsetY);
}

sf::FloatRect HitboxComponent::getGlobalBounds() const {
    return hitbox.getGlobalBounds();
}

const sf::FloatRect &HitboxComponent::getNextPosition(const sf::Vector2f &velocity) {
    nextPosition.left = hitbox.getPosition().x + velocity.x;
    nextPosition.top = hitbox.getPosition().y + velocity.y;
    return nextPosition;
}
