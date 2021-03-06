//
// Created by alpacox on 05/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_WEAPON_H
#define DRAGHI_E_SOTTERRANEI_WEAPON_H


class Weapon {
public:
    Weapon();
    virtual ~Weapon() {} // XXX polymorphic destructor !

    virtual int use() = 0;
    virtual Weapon* clone() const = 0;

    void setStrength(int s) {
        strength = s;
    }
    int getStrength() const {
        return strength;
    }

    void setMagic(bool m) {
        magic = m;
    }
    bool isMagic() const {
        return magic;
    }


protected:
    int strength; // tipo di dado col quale calcolare il danno
    bool magic;

};


#endif //DRAGHI_E_SOTTERRANEI_WEAPON_H
