//
// Created by gabriele on 03/12/21.
//

#include "precompiler.h"
#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(std::vector<Enemy*>& activeEnemies,
                             std::map<std::string, sf::Texture> &textures, GameCharacter& hero)
: textures(textures), activeEnemies(activeEnemies), hero(hero) {

}

EnemyFactory::~EnemyFactory() {

}

void EnemyFactory::createEnemy(short type, float xPos, float yPos, EnemySpawnerTile& enemy_spawner_tile) {
    switch(type){
        case static_cast<int>(EnemyTypes::MUMMY):{
            std::cout << "MUMMY" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 48, 48,
                                       8.f, 0, 1, 5, 1, 48, 48,
                                       12.f, 0, 3, 5, 3, 48, 48};
            float hitbox[4] = {20.f, 23.f, 25.f, 25};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["MUMMY_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        case static_cast<int>(EnemyTypes::SCORPION):{
            std::cout << "SCORPION" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 48, 48,
                                       8.f, 0, 1, 3, 1, 48, 48,
                                       12.f, 0, 3, 3, 3, 48, 48};
            float hitbox[4] = {20.f, 23.f, 25.f, 25};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["SCORPION_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        case static_cast<int>(EnemyTypes::VULTURE):{
            std::cout << "VULTURE" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 48, 48,
                                       8.f, 0, 1, 3, 1, 48, 48,
                                       12.f, 0, 3, 3, 3, 48, 48};
            float hitbox[4] = {20.f, 23.f, 25.f, 25};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["VULTURE_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        case static_cast<int>(EnemyTypes::HYENA):{
            std::cout << "HYENA" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 48, 48,
                                       8.f, 0, 1, 5, 1, 48, 48,
                                       12.f, 0, 3, 5, 3, 48, 48};
            float hitbox[4] = {10.f, 23.f, 35.f, 25};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["HYENA_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        case static_cast<int>(EnemyTypes::SNAKE):{
            std::cout << "SNAKE" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 48, 48,
                                       8.f, 0, 1, 3, 1, 48, 48,
                                       12.f, 0, 3, 3, 3, 48, 48};
            float hitbox[4] = {20.f, 33.f, 25.f, 15};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["SNAKE_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        case static_cast<int>(EnemyTypes::DECEASED):{
            std::cout << "DECEASED" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 48, 48,
                                       8.f, 0, 1, 5, 1, 48, 48,
                                       12.f, 0, 3, 5, 3, 48, 48};
            float hitbox[4] = {20.f, 23.f, 25.f, 25};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["DECEASED_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        case static_cast<int>(EnemyTypes::BIG_BLOATED):{
            std::cout << "BIG_BLOATED" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 72, 72,
                                       8.f, 0, 1, 5, 1, 72, 72,
                                       12.f, 0, 6, 3, 6, 72, 72};
            float hitbox[4] = {20.f, 23.f, 40.f, 40.f};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["BIG_BLOATED_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        case static_cast<int>(EnemyTypes::CENTIPEDE):{
            std::cout << "CENTIPEDE" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 72, 72,
                                       8.f, 0, 1, 3, 1, 72, 72,
                                       12.f, 0, 6, 3, 6, 72, 72};
            float hitbox[4] = {20.f, 23.f, 40.f, 40.f};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["CENTIPEDE_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        case static_cast<int>(EnemyTypes::BATTLE_TURTLE):{
            std::cout << "BATTLE_TURTLE" << "\n";
            float animations[3][7] = { 11.f, 0, 0, 3, 0, 72, 72,
                                       8.f, 0, 1, 3, 1, 72, 72,
                                       12.f, 0, 6, 3, 6, 72, 72};
            float hitbox[4] = {20.f, 33.f, 40.f, 30};
            activeEnemies.push_back(new Enemy(xPos, yPos, textures["BATTLE_TURTLE_SHEET"], enemy_spawner_tile, this->hero, animations, hitbox));

            enemy_spawner_tile.increaseEnemyCounter();
            break;
        }
        default:

            std::cout << "ERROR::ENEMYSYSTEM::CREATENEMY::TYPE DOES NOT EXIST" << "\n";
            break;
    }
}

void EnemyFactory::removeEnemy(const int index) {
    activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
    delete activeEnemies[index];
    activeEnemies.erase(activeEnemies.begin() + index);
}
