//
// Created by alpacox on 26/11/21.
//

#include "precompiler.h"
#include "SkillComponent.h"

/**************************  SKILL  ***************************/

SkillComponent::Skill::Skill(Skills type) {
    level = 1;
    levelCap = 99;
    exp = 0;
    expNext = 100;
}

SkillComponent::Skill::~Skill() {

}

const int SkillComponent::Skill::getType() const {
    return type;
}

void SkillComponent::Skill::gainExp(const int exp) {
    this->exp += exp;
    updateLevel();
}

void SkillComponent::Skill::updateLevel(const bool up) {

    /**
     * Aumenta o diminuisce il livello della skill a seconda che ci sia un deficit di exp o no.
     */

    if (up){
        if(level < levelCap){
            while (exp >= expNext){
                if (level < levelCap){
                    level++;
                    expNext = static_cast<int>(std::pow(level, 2) + level * 10 + level * 2);
                }
            }
        }
    }
    else{
        if(level > 0){
            while (exp < 0){
                if (level > 0){
                    level--;
                    expNext = static_cast<int>(std::pow(level, 2) + level * 10 + level * 2);
                }
            }
        }
    }
}

void SkillComponent::Skill::update() {

}


/**************************  SKILL COMPONENT  ***************************/


SkillComponent::SkillComponent() {

  skills.emplace_back(Skills::HEALTH);
  skills.emplace_back(Skills::ATTACK);
  skills.emplace_back(Skills::ACCURACY);
  skills.emplace_back(Skills::ENDURANCE);
}

SkillComponent::~SkillComponent() {

}

void SkillComponent::gainExp(const int skill, const int exp) {
    if(skills.empty() || skill < 0 || skill >= skills.size())
        throw("ERROR::SKILLCOMPONENT::GAINEXP::SKILL DOES NOT EXIST: " + skill);
    else
        skills[skill].gainExp(exp);
}
