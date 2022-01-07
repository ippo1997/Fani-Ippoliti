//
// Created by alpacox on 02/12/21.
//
#include "precompiler.h"
#include "Mummy.h"
/*
Mummy::Mummy(float x, float y, sf::Texture &texture_sheet, EnemySpawnerTile& enemy_spawner_tile, GameCharacter& hero)
      : Enemy(enemy_spawner_tile) {

    initVariables();
    initGUI();

    createHitboxComponent(this->sprite, 20.f, 23.f, 25.f, 25.f);
    createMovementComponent(50.f, 1600.f, 1000.f);
    createAnimationComponent(texture_sheet);
    createAttributeComponent(1);

    this->generateAttributes(attributeComponent->level);

    this->setPosition(x, y);
    initAnimations();

    follow = new AttackStrategy(*this, hero);
}

Mummy::~Mummy() {

    delete follow;
}

void Mummy::initVariables() {

}


void Mummy::initAnimations() {

    animationComponent->addAnimation("IDLE", 11.f, 0, 0, 3, 0, 48, 48);
    animationComponent->addAnimation("WALK", 8.f, 0, 1, 5, 1, 48, 48);
    animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 5, 2, 48, 48);
    animationComponent->addAnimation("DEATH", 12.f, 0, 3, 5, 3, 48, 48);
    animationComponent->addAnimation("HURT", 7.f, 0, 4, 1, 4, 48, 48);
}

void Mummy::initGUI() {

    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(40.f, 5.f));
    hpBar.setPosition(sprite.getPosition().x + 12.f , sprite.getPosition().y);
}

void Mummy::updateAnimation(const float &dt) {

    if(movementComponent->getState(IDLE))
        animationComponent->play("IDLE", dt);
    else if (movementComponent->getState(MOVING_RIGHT)){
        if(sprite.getScale().x > 0.f){ // <
            sprite.setOrigin(64.f, 0.f);  // 0, 0
            sprite.setScale(-1.f, 1.f); // 1, 1
        }
        animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MOVING_LEFT)){
        if(sprite.getScale().x < 0.f) { // >
            sprite.setOrigin(0.f, 0.f); // 30, 0
            sprite.setScale(1.f, 1.f); // -1, 1
        }
        animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MOVING_UP)){
        animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MOVING_DOWN)){
        animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
    }
    if(damageTimer.getElapsedTime().asMilliseconds() <= damageTimerMax){
        //this->animationComponent->play("HURT", dt, true);
        sprite.setColor(sf::Color::Red);
    }
    else
        sprite.setColor(sf::Color::White);

//TODO animazioni di morte
    if(isDead()){
        this->animationComponent->play("DEATH", dt, true);

    }


}

void Mummy::update(const float &dt, sf::Vector2f& mouse_pos_view, const sf::View& view) {

    Enemy::update(dt, mouse_pos_view, view);
    movementComponent->update(dt);

    hpBar.setSize(sf::Vector2f(40.f * (static_cast<float>(attributeComponent->hp) / attributeComponent->hpMax), 5.f));
    hpBar.setPosition(sprite.getPosition().x + 12.f , sprite.getPosition().y); //TEST. DA RIMUOVERE!!!

    //this->updateAttack();
    updateAnimation(dt);
    hitboxComponent->update();
    follow->update(dt);
}

void Mummy::render(sf::RenderTarget &target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox) {
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


*/

