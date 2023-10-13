//
// Created by alpacox on 16/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_SUBJECT_H
#define DRAGHI_E_SOTTERRANEI_SUBJECT_H

#include "Observer.h"


class Subject
{
public:
    virtual ~Subject(){};
    virtual void Attach(Observer *observer) = 0;
    virtual void Detach(Observer *observer) = 0;
    virtual void Notify() = 0;
};

#endif //DRAGHI_E_SOTTERRANEI_SUBJECT_H
