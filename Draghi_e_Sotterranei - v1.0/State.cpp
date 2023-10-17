//
// Created by alpacox on 26/03/21.
//

#include "precompiler.h"
#include "State.h"

State::State(StateData* state_data) {
    stateData = state_data;
    window = state_data->windowData;
    supportedKeys = state_data->supportedKeysData;
    states = state_data->states;
    quit = false;
    paused = false;
    gameOver = false;
    win = false;
    keyTime = 0.f;
    keyTimeMax = 25.f;
    gridSize = state_data->gridSize;
}

State::~State() {
    
}

const bool & State::getQuit() const {
    return quit;
}

bool State::getKeyTime() {
    if(keyTime >= keyTimeMax){
        keyTime = 0.f;
        return true;
    }
    return false;
}

void State::endState() {
    quit = true;
}

void State::pauseState() {
    paused = true;
}

void State::unpauseState() {
    paused = false;
}

void State::updateMousePosition(sf::View* view) {
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*window);
   if(view)
       window->setView(*view);
    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    mousePosGrid = sf::Vector2i(
            static_cast<int>(mousePosView.x) / static_cast<int>(gridSize) ,
            static_cast<int>(mousePosView.y) / static_cast<int>(gridSize)
    );
    window->setView(window->getDefaultView());
}

void State::updateKeyTime(const float& dt) {
    if(keyTime < keyTimeMax)
        keyTime += 100.f * dt;
}



