//
// Created by alpacox on 01/10/21.
//

#include "precompiler.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
: sprite(sprite), maxVelocity(maxVelocity), accelleration(acceleration), deceleration(deceleration){

}

MovementComponent::~MovementComponent() {

}

void MovementComponent::update(const float &dt) {
    if(velocity.x > 0.f) {
        if(velocity.x > maxVelocity)
            velocity.x = maxVelocity;

        velocity.x -= deceleration * dt;
        if(velocity.x < 0.f)
            velocity.x = 0.f;
    }
    else if(velocity.x < 0.f){
        if (velocity.x < - maxVelocity)
            velocity.x = - maxVelocity;

        velocity.x += deceleration * dt;
        if(velocity.x > 0.f)
            velocity.x = 0.f;
    }

    if(velocity.y > 0.f) {
        if(velocity.y > maxVelocity)
            velocity.y = maxVelocity;

        velocity.y -= deceleration * dt;
        if(velocity.y < 0.f)
            velocity.y = 0.f;
    }
    else if(velocity.y < 0.f){
        if (velocity.y < - maxVelocity)
            velocity.y = - maxVelocity;

        velocity.y += deceleration * dt;
        if(velocity.y > 0.f)
            velocity.y = 0.f;
    }

    sprite.move(velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) {
    velocity.x += accelleration * dir_x * dt;
    velocity.y += accelleration * dir_y * dt;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return velocity;
}


bool MovementComponent::getState(MovementStates state) const {
    switch (state){
        case MovementStates::IDLE:
            if(velocity.x == 0.f && velocity.y == 0.f)
                return true;
            break;

        case MovementStates::MOVING:
            if(velocity.x != 0.f && velocity.y != 0.f)
                return true;
            break;

        case MovementStates::MOVING_RIGHT:
            if(velocity.x > 0.f)
                return true;
            break;

        case MovementStates::MOVING_LEFT:
            if(velocity.x < 0.f)
                return true;
            break;

        case MovementStates::MOVING_UP:
            if(velocity.y < 0.f)
                return true;
            break;

        case MovementStates::MOVING_DOWN:
            if(velocity.y > 0.f)
                return true;
            break;
    }
    return false;
}

const float &MovementComponent::getMaxVelocity() const {
    return maxVelocity;
}

void MovementComponent::stopVelocityX() {
    velocity.x = 0.f;
}

void MovementComponent::stopVelocityY() {
    velocity.y = 0.f;
}
