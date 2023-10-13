//
// Created by alpacox on 05/10/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_HITBOXCOMPONENT_H
#define DRAGHI_E_SOTTERRANEI_HITBOXCOMPONENT_H


class HitboxComponent {
public:
    HitboxComponent(sf::Sprite& sprite,
                    float offset_x, float offset_y,
                    float width, float height);
    virtual ~HitboxComponent();

    const sf::Vector2f& getPosition() const;
    sf::FloatRect  getGlobalBounds() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

    void setPosition(const sf::Vector2f& position);
    void setPosition( float x,  float y);

    bool intersect(const sf::FloatRect& frect);

     void update();
     void render(sf::RenderTarget& target);

private:
    sf::RectangleShape hitbox;
    sf::Sprite& sprite;
    sf::FloatRect  nextPosition;
    float offsetX;
    float offsetY;

};


#endif //DRAGHI_E_SOTTERRANEI_HITBOXCOMPONENT_H
