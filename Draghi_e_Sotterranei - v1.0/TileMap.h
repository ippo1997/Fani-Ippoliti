//
// Created by alpacox on 25/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_TILEMAP_H
#define DRAGHI_E_SOTTERRANEI_TILEMAP_H

#include "EnemySpawnerTile.h"
#include "RegularTile.h"
#include "EnemyFactory.h"

class Tile;
class GameCharacter;
class EnemySpawnerTile;

class TileMap {
public:
    TileMap(float gridSize, int  width, int  height, std::string texture_file);
    explicit TileMap( std::string file_name);
    virtual ~TileMap();

    bool tileEmpty( int x,  int y,  int z) const;
    const sf::Texture* getTileSheet() const;
    int getLayerSize( int x,  int y,  int layer) const;
    const sf::Vector2f& getMaxSizeF() const;

    void addTile( int x,  int y,  int z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
    void addTile( int x,  int y,  int z, const sf::IntRect& texture_rect,
                  int enemy_type,  int enemy_amount,  int enemy_tts,  int enemy_md);

    void removeTile( int x,  int y,  int z,  int type = -1);
    void saveToFile( std::string file_name);
    void loadFromFile( std::string file_name);

    void updateWorldBoundsCollision(GameCharacter* gameCharacter, const float& dt);
    void updateTileCollision(GameCharacter* gameCharacter, const float& dt);
    void updateTiles(GameCharacter* gameCharacter, const float& dt, EnemyFactory& enemyStrategy);
    void update(GameCharacter* gameCharacter, const float& dt);
    void render(
            sf::RenderTarget& target,
            const sf::Vector2i& gridPosition,
            sf::Shader* shader = nullptr,
             sf::Vector2f heroPosition = sf::Vector2f(),
             bool show_collision = false
                    );
    void renderDeferred(sf::RenderTarget& target, sf::Shader* shader = nullptr,  sf::Vector2f heroPosition = sf::Vector2f());

private:
    float gridSizeF;
    int gridSizeI;
    sf::Vector2i maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
    int layers;
    std::vector< std::vector< std::vector< std::vector< Tile*> > > > map;
    std::stack<Tile*> deferredRenderStack;
    std::string  textureFile;
    sf::Texture tileSheet;
    sf::RectangleShape collisionBox;

    void clear();

    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;

};

#endif //DRAGHI_E_SOTTERRANEI_TILEMAP_H
