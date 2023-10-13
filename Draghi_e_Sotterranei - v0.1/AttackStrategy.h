//
// Created by gabriele on 13/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_ATTACKSTRATEGY_H
#define DRAGHI_E_SOTTERRANEI_ATTACKSTRATEGY_H

#include "EnemyStrategy.h"

class AttackStrategy : public EnemyStrategy {
public:
    AttackStrategy(GameCharacter &self, GameCharacter &gameCharacter);
    ~AttackStrategy();

    void update(const float& dt) override;

    bool isMoving() const;

protected:
    bool hunting;

};


#endif //DRAGHI_E_SOTTERRANEI_ATTACKSTRATEGY_H
