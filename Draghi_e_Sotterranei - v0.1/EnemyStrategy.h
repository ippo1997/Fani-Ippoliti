//
// Created by gabriele on 13/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_ENEMYSTRATEGY_H
#define DRAGHI_E_SOTTERRANEI_ENEMYSTRATEGY_H

#include "GameCharacter.h"

class EnemyStrategy {
public:
    EnemyStrategy(GameCharacter& self, GameCharacter& gameCharacter);

    virtual void update(const float& dt) = 0;

protected:
    GameCharacter& self;
    GameCharacter& gameCharacter;

};


#endif //DRAGHI_E_SOTTERRANEI_ENEMYSTRATEGY_H
