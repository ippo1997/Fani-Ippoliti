//
// Created by alpacox on 29/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_ENEMYSPAWNERTILE_H
#define DRAGHI_E_SOTTERRANEI_ENEMYSPAWNERTILE_H

#include "Tile.h"


class EnemySpawnerTile:
        public Tile {
public:
    EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF,
                     const sf::Texture& texture, const sf::IntRect& texture_rect,
                     int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);

    EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);

    virtual ~EnemySpawnerTile();

    const std::string getAsString() const override;
    const int& getEnemyCounter() const;
    const int& getEnemyAmount() const;
    bool getSpawnTimer();
    const int& getEnemyType() const;

    void increaseEnemyCounter();
    void decreaseEnemyCounter();

    void update() override;
    void render(sf::RenderTarget &target, sf::Shader* shader = nullptr, sf::Vector2f hero_position = sf::Vector2f()) override;

private:
    float gridSize;
    int enemyType;
    int enemyAmount;
    int enemyCounter;
    sf::Clock enemySpawnTimer;
    sf::Int32 enemyTimeToSpawn;
    float enemyMaxDistance;
    bool firstSpawn;

};


#endif //DRAGHI_E_SOTTERRANEI_ENEMYSPAWNERTILE_H
