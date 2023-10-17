//
// Created by gabriele on 21/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_GAMEMANAGER_H
#define DRAGHI_E_SOTTERRANEI_GAMEMANAGER_H

#include <utility>

#include "precompiler.h"
#include "Subject.h"

class GameManager:
        public Subject{

public:
    virtual ~GameManager() {
        //std::cout << "Goodbye, I was the Subject.\n"; //debug
    }

/// The subscription management methods.

    void Attach(Observer *observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(Observer *observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
        std::list<Observer *>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = std::move(message);
        Notify();
    }

    void HowManyObserver() {
        //std::cout << "There are " << list_observer_.size() << " observers in the list.\n"; //debug
    }

    void SomeBusinessLogic() {
        //this->message_ = "change message message"; //debug
        Notify();
        //std::cout << "I'm about to do some thing important\n"; //debug
    }

    void updateKills() {
        kills++;
    }

    int getKills() const{
        return kills;
    }

private:
    std::list<Observer *> list_observer_;
    std::string message_;
    int kills = 0;
};


#endif //DRAGHI_E_SOTTERRANEI_GAMEMANAGER_H
