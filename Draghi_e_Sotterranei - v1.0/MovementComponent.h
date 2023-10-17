//
// Created by alpacox on 01/10/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_MOVEMENTCOMPONENT_H
#define DRAGHI_E_SOTTERRANEI_MOVEMENTCOMPONENT_H


enum class MovementStates {IDLE, MOVING,  MOVING_RIGHT, MOVING_LEFT, MOVING_UP, MOVING_DOWN};

class MovementComponent {
public:
    MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
    ~MovementComponent();

    const float& getMaxVelocity() const;
    const sf::Vector2f& getVelocity() const;
    bool getState(MovementStates state) const;

    void stopVelocityX();
    void stopVelocityY();

    void move(float x,  float y, const float& dt);
    void update(const float& dt);

private:
    sf::Sprite& sprite;

    float maxVelocity;
    float accelleration;
    float deceleration;

    sf::Vector2f velocity;

};


#endif //DRAGHI_E_SOTTERRANEI_MOVEMENTCOMPONENT_H
