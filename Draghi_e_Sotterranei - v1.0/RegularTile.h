//
// Created by gabriele on 03/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_REGULARTILE_H
#define DRAGHI_E_SOTTERRANEI_REGULARTILE_H

#include "Tile.h"

class RegularTile : public Tile {
public:
    RegularTile(short type, int grid_x, int grid_y, float gridSizeF,
         const sf::Texture& texture, const sf::IntRect& texture_rect,
         bool collision = false);
    ~RegularTile() override;

    const std::string getAsString() const override;
    void update() override;
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, sf::Vector2f hero_position = sf::Vector2f()) override;

};


#endif //DRAGHI_E_SOTTERRANEI_REGULARTILE_H
