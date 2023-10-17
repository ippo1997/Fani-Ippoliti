//
// Created by alpacox on 30/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_GAME_H
#define DRAGHI_E_SOTTERRANEI_GAME_H

#include "State.h"
#include "GameCharacter.h"
#include "Hero.h"
#include "MainMenuState.h"

class State;
class GameCharacter;
class Hero;
class MainMenuState;

using namespace std;

class Game {
public:
    Game();
    virtual ~Game();

    void updateDt();
    void update();
    void render();
    void run();
    void updateSFMLEvents();

private:
    GraphicsSettings gfxSettings;
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;

    stack<State*> states;

    map<string, int> supportedKeys;

    float gridSize;

    void initVariables();
    void initGraphicsSettings();
    void initStateData();
    void initWindow();
    void initKeys();
    void initStates();
    void endApplication();

};


#endif //DRAGHI_E_SOTTERRANEI_GAME_H
