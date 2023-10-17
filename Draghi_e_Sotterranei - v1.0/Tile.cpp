//
// Created by alpacox on 07/10/21.
//

#include "precompiler.h"
#include "Tile.h"

Tile::Tile() {
    collision = false;
    type = 0;
}

Tile::Tile(short type, int grid_x, int grid_y, float gridSizeF,
           const sf::Texture& texture, const sf::IntRect& texture_rect,
           const bool collision) {
    shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
    shape.setTexture(texture);
    shape.setTextureRect(texture_rect);
    this->collision = collision;
    this->type = type;
}

Tile::~Tile() {

}

const sf::Vector2f &Tile::getPosition() const {
    return shape.getPosition();
}

bool Tile::intersects(const sf::FloatRect bounds) const{
    return  shape.getGlobalBounds().intersects(bounds);
}

sf::FloatRect Tile::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

const bool & Tile::getCollision() const {
    return collision;
}

const short &Tile::getType() const {
    return type;
}
