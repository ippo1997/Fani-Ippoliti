//
// Created by gabriele on 03/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_ENEMYFACTORY_H
#define DRAGHI_E_SOTTERRANEI_ENEMYFACTORY_H

#include "EnemySpawnerTile.h"
#include "Enemy.h"

enum class EnemyTypes {MUMMY = 0, SCORPION, VULTURE, HYENA, SNAKE, DECEASED, BIG_BLOATED, CENTIPEDE, BATTLE_TURTLE};

class EnemyFactory {
public:
    EnemyFactory(std::vector<Enemy*>& activeEnemies,
                  std::map<std::string, sf::Texture>& textures, GameCharacter& hero);
    virtual ~EnemyFactory();

    void createEnemy(short type, float xPos, float yPos, EnemySpawnerTile& enemy_spawner_tile);
    void removeEnemy(int index);

private:
    std::map<std::string, sf::Texture>& textures;
    std::vector<Enemy*>& activeEnemies;
    GameCharacter& hero;

};


#endif //DRAGHI_E_SOTTERRANEI_ENEMYFACTORY_H
