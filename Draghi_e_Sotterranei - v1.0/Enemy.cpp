//
// Created by alpacox on 05/03/21.
//

#include "precompiler.h"
#include "Enemy.h"

Enemy::Enemy(float x, float y,
             sf::Texture& texture_sheet,
             EnemySpawnerTile& enemy_spawner_tile,
             GameCharacter& hero,
             float animations_parameters[3][7],
             float hitbox_parameters[4])
             : enemySpawnerTile(enemy_spawner_tile) {

    initVariables();
    initGUI();

    createHitboxComponent(this->sprite, hitbox_parameters[0], hitbox_parameters[1], hitbox_parameters[2], hitbox_parameters[3]);
    createMovementComponent(50.f, 1600.f, 1000.f);
    createAnimationComponent(texture_sheet);
    createAttributeComponent(1);

    this->generateAttributes(attributeComponent->level);

    this->setPosition(x, y);
    initAnimations(animations_parameters);

    follow = new AttackStrategy(*this, hero);
}

Enemy::Enemy(float x, float y, EnemySpawnerTile& enemy_spawner_tile, GameCharacter &hero)
: enemySpawnerTile(enemy_spawner_tile) {

    initVariables();

    createMovementComponent(50.f, 1600.f, 1000.f);
    createAttributeComponent(1);

    this->generateAttributes(attributeComponent->level);

    this->setPosition(x, y);

    follow = new AttackStrategy(*this, hero);

}

Enemy::~Enemy() {

    delete follow;
}

void Enemy::initVariables() {
    gainExp = 10;
    damageTimerMax = 1000;
    despawnTimerMax = 1000;
}



const unsigned &Enemy::getGainExp() const {

    return gainExp;
}

EnemySpawnerTile &Enemy::getEnemySpawnerTile() {
    return enemySpawnerTile;
}

bool Enemy::getDamageTimerDone() const{

    return damageTimer.getElapsedTime().asMilliseconds() >= damageTimerMax;
}

bool Enemy::getDespawnTimerDone() const{

    return despawnTimer.getElapsedTime().asMilliseconds() >= despawnTimerMax;
}

void Enemy::resetDamageTimer() {

    damageTimer.restart();
}

void Enemy::generateAttributes(const unsigned int &level) {

    gainExp = level * (rand() % 5 +1);
}

void Enemy::loseHP(const int hp) {
    if(attributeComponent) {
        attributeComponent->loseHP(hp);
    }
}

const AttributeComponent *Enemy::getAttributeComp() const {
    if(attributeComponent)
        return attributeComponent;
    else {
        std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INIZIALIZES" << "\n";
        return nullptr;
    }
}

bool Enemy::isDead() const {
    if(attributeComponent){
        return attributeComponent->isDead();
    }
    return false;
}

void Enemy::initAnimations(float animationsParameters[3][7]) {

    animationComponent->addAnimation("IDLE", animationsParameters[0][0], static_cast<int>(animationsParameters[0][1]), static_cast<int>(animationsParameters[0][2]), static_cast<int>(animationsParameters[0][3]), static_cast<int>(animationsParameters[0][4]), static_cast<int>(animationsParameters[0][5]), static_cast<int>(animationsParameters[0][6]));
    animationComponent->addAnimation("WALK", animationsParameters[1][0], static_cast<int>(animationsParameters[1][1]), static_cast<int>(animationsParameters[1][2]), static_cast<int>(animationsParameters[1][3]), static_cast<int>(animationsParameters[1][4]), static_cast<int>(animationsParameters[1][5]), static_cast<int>(animationsParameters[1][6]));
    animationComponent->addAnimation("DEATH", animationsParameters[2][0], static_cast<int>(animationsParameters[2][1]), static_cast<int>(animationsParameters[2][2]), static_cast<int>(animationsParameters[2][3]), static_cast<int>(animationsParameters[2][4]), static_cast<int>(animationsParameters[2][5]), static_cast<int>(animationsParameters[2][6]));
}

void Enemy::initGUI() {

    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(40.f, 5.f));
    hpBar.setPosition(sprite.getPosition().x + 12.f , sprite.getPosition().y);
}

void Enemy::updateAnimation(const float &dt) {

    if(movementComponent->getState(MovementStates::IDLE))
        animationComponent->play("IDLE", dt);
    else if (movementComponent->getState(MovementStates::MOVING_RIGHT)){
        if(sprite.getScale().x > 0.f){ // <
            sprite.setOrigin(64.f, 0.f);  // 0, 0
            sprite.setScale(-1.f, 1.f); // 1, 1
        }
        animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MovementStates::MOVING_LEFT)){
        if(sprite.getScale().x < 0.f) { // >
            sprite.setOrigin(0.f, 0.f); // 30, 0
            sprite.setScale(1.f, 1.f); // -1, 1
        }
        animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MovementStates::MOVING_UP)){
        animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MovementStates::MOVING_DOWN)){
        animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
    }
    if(damageTimer.getElapsedTime().asMilliseconds() <= damageTimerMax){
        //this->animationComponent->play("HURT", dt, true);
        sprite.setColor(sf::Color::Red);
    }
    else
        sprite.setColor(sf::Color::White);

    if(isDead())
        this->animationComponent->play("DEATH", dt, true);
}

void Enemy::update(const float &dt, sf::Vector2f &mouse_pos_view, const sf::View& view) {

    if(vectorDistance(getPosition(), view. getCenter()) < 1500.f)
        despawnTimer.restart();

    movementComponent->update(dt);

    hpBar.setSize(sf::Vector2f(40.f * (static_cast<float>(attributeComponent->hp) / attributeComponent->hpMax), 5.f));
    hpBar.setPosition(sprite.getPosition().x + 12.f , sprite.getPosition().y); //TEST. DA RIMUOVERE!!!

    updateAnimation(dt);
    hitboxComponent->update();
    follow->update(dt);


}

void Enemy::render(sf::RenderTarget &target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox) {
    if(shader){
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_position);

        target.draw(sprite, shader);
        target.draw(hpBar, shader);
    }
    else{
        target.draw(sprite);
        target.draw(hpBar);
    }

    if(show_hitbox)
        hitboxComponent->render(target);
}


