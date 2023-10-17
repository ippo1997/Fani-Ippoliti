//
// Created by alpacox on 15/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_ACHIEVEMENTS_H
#define DRAGHI_E_SOTTERRANEI_ACHIEVEMENTS_H

#include "precompiler.h"
#include "Observer.h"
#include "GameManager.h"


class Achievements : public Observer {

public:
    Achievements(GameManager &gameManager) : gameManager_(gameManager) {
        this->gameManager_.Attach(this);
        //std::cout << "Hi, I'm the Observer \"" << ++Achievements::static_number_ << "\".\n"; //debug
        this->number_ = Achievements::static_number_;

    }
    virtual ~Achievements() {
        //std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n"; //debug
    }

    void Update(const std::string &message_from_subject) override {
        message_from_gameManager_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        gameManager_.Detach(this);
        //std::cout << "Observer \"" << number_ << "\" removed from the list.\n"; //debug
    }
    void PrintInfo() {
        std::cout << "\nAchievement unlocked: " << this->message_from_gameManager_ << "\n";

    }

private:
    std::string message_from_gameManager_;
    GameManager &gameManager_;
    int static_number_{};
    int number_;

};

#endif //DRAGHI_E_SOTTERRANEI_ACHIEVEMENTS_H
