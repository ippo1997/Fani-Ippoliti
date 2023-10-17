//
// Created by gabriele on 13/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_ATTRIBUTECOMPONENT_H
#define DRAGHI_E_SOTTERRANEI_ATTRIBUTECOMPONENT_H


class AttributeComponent {

public:
    explicit AttributeComponent(int level);
    virtual ~AttributeComponent();

    int level;
    int exp;
    int expNext;
    int attributePoints;
    int strength;
    int vitality;
    int intelligence;

    int hp;
    int hpMax;
    int damageMin;
    int damageMax;

    void updateStats(bool reset);
    void updateLevel();
    void update();

    void loseHP(int hp);
    void gainEXP(int exp);

    bool isDead() const;
};


#endif //DRAGHI_E_SOTTERRANEI_ATTRIBUTECOMPONENT_H