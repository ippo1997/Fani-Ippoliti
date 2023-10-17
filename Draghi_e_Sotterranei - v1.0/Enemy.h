//
// Created by alpacox on 05/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_ENEMY_H
#define DRAGHI_E_SOTTERRANEI_ENEMY_H

#include "GameCharacter.h"
#include "EnemySpawnerTile.h"
#include "AttackStrategy.h"


class Enemy : public GameCharacter {
public:
    Enemy(float x, float y,
          sf::Texture& texture_sheet,
          EnemySpawnerTile& enemy_spawner_tile,
          GameCharacter& hero,
          float animations_parameters[3][7],
          float hitbox_parameters[4]);
    Enemy(float x, float y, EnemySpawnerTile& enemy_spawner_tile, GameCharacter& hero);
    virtual ~Enemy();

    const unsigned& getGainExp() const;
    EnemySpawnerTile& getEnemySpawnerTile();
    bool getDamageTimerDone() const;
    bool getDespawnTimerDone() const;

    void resetDamageTimer();

    virtual void generateAttributes(const unsigned& level);

    virtual void loseHP( int hp);
    virtual bool isDead() const;

    virtual const AttributeComponent* getAttributeComp() const;

    void updateAnimation(const float& dt);
    void update(const float &dt, sf::Vector2f& mouse_pos_view, const sf::View& view) override;
    void render(sf::RenderTarget &target, sf::Shader* shader = nullptr,  sf::Vector2f light_position = sf::Vector2f(),  bool show_hitbox = false) override;

protected:
    EnemySpawnerTile& enemySpawnerTile;
    unsigned gainExp;
    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;
    sf::Clock despawnTimer;
    sf::Int32 despawnTimerMax;

    void initGUI();

    sf::RectangleShape hpBar;

    AttackStrategy* follow;

     void initVariables();
     void initAnimations(float animationsParameters[3][7]);
};


#endif //DRAGHI_E_SOTTERRANEI_ENEMY_H
