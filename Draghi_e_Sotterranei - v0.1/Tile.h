//
// Created by alpacox on 07/10/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_TILE_H
#define DRAGHI_E_SOTTERRANEI_TILE_H

enum class TileTypes {DEFAULT = 0, DAMAGING, FLAVOUR, ENEMYSPAWNER};

class Tile {
public:
    Tile();
    Tile(short type, int grid_x, int grid_y, float gridSizeF,
         const sf::Texture& texture, const sf::IntRect& texture_rect,
          bool collision);
    virtual ~Tile();

    const short& getType() const;
    virtual const bool & getCollision() const;
    virtual  void setCollision(bool col){ collision = col;};

    virtual const sf::Vector2f& getPosition() const;
    virtual sf::FloatRect getGlobalBounds() const;
    virtual bool intersects( sf::FloatRect bounds) const;
    virtual const std::string getAsString() const = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr,  sf::Vector2f hero_position = sf::Vector2f()) = 0;

protected:
    sf::Sprite shape;
    short type;
    bool collision;

};

#endif //DRAGHI_E_SOTTERRANEI_TILE_H
