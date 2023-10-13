//
// Created by alpacox on 26/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_SKILLCOMPONENT_H
#define DRAGHI_E_SOTTERRANEI_SKILLCOMPONENT_H

enum class Skills {HEALTH = 0, ATTACK, ACCURACY, ENDURANCE};

class SkillComponent {
public:
    SkillComponent();
    virtual ~SkillComponent();

    void gainExp( int skill,  int exp);

private:
    class Skill{

    public:
        Skill(Skills type);
        ~Skill();

        const int getType() const;

        void gainExp( int exp);

        void updateLevel( bool up = true);
        void update();

    private:
        int type;
        int level;
        int levelCap;
        int exp;
        int expNext;
    };

    std::vector<Skill> skills;

};


#endif //DRAGHI_E_SOTTERRANEI_SKILLCOMPONENT_H
