//
// Created by alpacox on 05/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_GAMECHARACTER_H
#define DRAGHI_E_SOTTERRANEI_GAMECHARACTER_H


#include "Weapon.h"

class GameCharacter {
public:
    GameCharacter();
    virtual ~GameCharacter(); // XXX polymorphic destructor !


    virtual int fight(GameCharacter &enemy) = 0;
    bool isLegalFight(const GameCharacter &enemy) const;

    virtual int receiveDamage(int points); // we want to override it: must be virtual



    int getPosX() const {
        return posX;
    }
    void setPosX(int posX) {
        GameCharacter::posX = posX;
    }
    int getPosY() const {
        return posY;
    }
    void setPosY(int posY) {
        GameCharacter::posY = posY;
    }

    int getHealth() const;
    void setHealth(int hp);

    Weapon* getWeapon();
    void setWeapon(Weapon* weapon);

    int getArmor() const;
    void setArmor(int ac);

    int getStrenght();
    void setStrenght();

    int getIntelligence();
    void setIntelligence();

    int basicFight();




// easier to access in derived classes if protected
protected:
    int health;
    int armorClass;
    int intelligence;
    int strenght;
    int posX;
    int posY;
    Weapon* weapon;

};


#endif //DRAGHI_E_SOTTERRANEI_GAMECHARACTER_H
