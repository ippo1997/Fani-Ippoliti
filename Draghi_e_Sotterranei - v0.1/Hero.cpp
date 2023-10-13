//
// Created by alpacox on 05/03/21.
//

#include "precompiler.h"
#include "Hero.h"

Hero::Hero(float x, float y, sf::Texture& texture_sheet) {
    initVariables();

    createHitboxComponent(this->sprite, 7.f, 23.f, 20.f, 25.f);
    createMovementComponent(140.f, 1500.f, 500.f);
    createAnimationComponent(texture_sheet);
    createAttributeComponent(1);
    createSkillComponent();

    this->setPosition(x, y);
    initAnimations();
}

Hero::~Hero() {
    delete weapon;
}

void Hero::initVariables() {
    initAttack = false;
    attacking = false;
    weapon = new Sword(1, 2, 5, 65, 20, "./Resources/Images/Sprites/Weapons/weapon.png");
    weapon->generate(1, 3);

    damageTimerMax = 1000;
}

void Hero::initAnimations() {
    animationComponent->addAnimation("IDLE", 11.f, 0, 0, 3, 0, 48, 48);
    animationComponent->addAnimation("WALK", 8.f, 0, 1, 5, 1, 48, 48);
    animationComponent->addAnimation("ATTACK1", 6.f, 0, 2, 5, 2, 48, 48);
    animationComponent->addAnimation("ATTACK2", 7.f, 0, 3, 5, 3, 48, 48);
    animationComponent->addAnimation("ATTACK3", 7.f, 0, 4, 5, 4, 48, 48);
    animationComponent->addAnimation("DEATH", 12.f, 0, 5, 5, 5, 48, 48);
    animationComponent->addAnimation("HURT", 7.f, 0, 6, 2, 6, 48, 48);
    animationComponent->addAnimation("JUMP", 7.f, 0, 7, 5, 7, 48, 48);
    animationComponent->addAnimation("RUN", 6.f, 0, 8, 5, 8, 48, 48);
}

AttributeComponent *Hero::getAttributeComponent() {
    return attributeComponent;
}

Weapon *Hero::getWeapon() const {
    return weapon;
}

const std::string Hero::toStringCharacterTab() const {
    std::stringstream ss;
    const AttributeComponent* ac = this->attributeComponent;
    const Weapon* w = this->weapon;
    ss << "Level: " << ac->level << "\n"
       << "Experience: " << ac->exp << "\n"
       << "Exp next: " << ac->expNext << "\n"
       << "Weapon Level: " << w->getLevel() << "\n"
       << "Weapon Type: " << (bool) w->getType() << "\n"
       << "Weapon Value: " << w->getValue() << "\n"
       << "Weapon Range: " << w->getRange() << "\n"
       << "Weapon Damage Min: " << w->getDamageMin() + this->attributeComponent->damageMin << " (" << this->attributeComponent->damageMin << ") " << "\n"
       << "Weapon Damage Max: " << w->getDamageMax() + this->attributeComponent->damageMax << " (" << this->attributeComponent->damageMax << ") " << "\n";
    return ss.str();
}

const bool &Hero::getInitAttack() const {
    return initAttack;
}

void Hero::setInitAttack(const bool initAttack) {
    this->initAttack = initAttack;
}

bool Hero::getDamageTimer() {
    if(damageTimer.getElapsedTime().asMilliseconds() >= damageTimerMax){
        damageTimer.restart();
        return true;
    }
    else
        return false;
}

unsigned Hero::getDamage() const {
    return rand() % (
            (attributeComponent->damageMax + weapon->getDamageMax())
            - (attributeComponent->damageMin + weapon->getDamageMin()) + 1)
            + (attributeComponent->damageMin + weapon->getDamageMin());
}

void Hero::loseHP(const int hp) {
    attributeComponent->loseHP(hp);
}

void Hero::gainEXP(const int exp) {
    attributeComponent->gainEXP(exp);
}

void Hero::updateAnimation(const float &dt) {
    if(attacking && animationComponent->play("ATTACK1", dt, true))
            attacking = false;

    if(movementComponent->getState(MovementStates::IDLE))
        animationComponent->play("IDLE", dt);
    else if (movementComponent->getState(MovementStates::MOVING_RIGHT)){
        if(sprite.getScale().x < 0.f){
            sprite.setOrigin(0.f, 0.f);
            sprite.setScale(1.f, 1.f);
        }
        animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MovementStates::MOVING_LEFT)){
        if(sprite.getScale().x > 0.f) {
            sprite.setOrigin(30.f, 0.f);
            sprite.setScale(-1.f, 1.f);
        }
        animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MovementStates::MOVING_UP)){
        animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
    }
    else if(movementComponent->getState(MovementStates::MOVING_DOWN)){
        this->animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
    }

    if(damageTimer.getElapsedTime().asMilliseconds() <= damageTimerMax)
        sprite.setColor(sf::Color::Red);
    else
        sprite.setColor(sf::Color::White);

    if(isDead())
        this->animationComponent->play("DEATH", dt, true);
}

void Hero::update(const float &dt, sf::Vector2f& mouse_pos_view, const sf::View& view) {
    movementComponent->update(dt);
    updateAnimation(dt);
    hitboxComponent->update();
    weapon->update(mouse_pos_view, sf::Vector2f(getSpriteCenter().x, getSpriteCenter().y + 5.f));
}

void Hero::render(sf::RenderTarget &target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox) {
    if(shader){
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_position);
        target.draw(sprite, shader);

        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_position);
        weapon->render(target, shader);
    }
    else{
        target.draw(sprite);
        weapon->render(target);
    }

    if(show_hitbox)
        hitboxComponent->render(target);
}

void Hero::updateAttack() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        attacking = true;
}

bool Hero::isDead() const {
    if(attributeComponent)
        return attributeComponent->isDead();
    return false;
}


