//
// Created by alpacox on 15/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_OBSERVER_H
#define DRAGHI_E_SOTTERRANEI_OBSERVER_H

#include "GameCharacter.h"

class Observer {
public:
    virtual ~Observer(){};
    virtual void Update(const std::string &message_from_subject) = 0;

};

#endif //DRAGHI_E_SOTTERRANEI_OBSERVER_H
