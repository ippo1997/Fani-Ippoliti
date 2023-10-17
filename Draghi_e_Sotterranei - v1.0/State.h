//
// Created by alpacox on 26/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_STATE_H
#define DRAGHI_E_SOTTERRANEI_STATE_H

#include "GraphicsSettings.h"
#include "Hero.h"

class GraphicsSettings;
class Hero;
class State;

struct StateData{
public:
    StateData() {};
    float gridSize;
    sf::RenderWindow* windowData;
    GraphicsSettings* gfxSettings;
    std::map<std::string, int>* supportedKeysData;
    std::stack<State*>* states;
};

class State {
public:
    State(StateData* state_data);
    virtual ~State();

    const bool& getQuit() const;

    virtual bool getKeyTime();

    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePosition(sf::View* view = nullptr);
    virtual void updateKeyTime(const float& dt);
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
    StateData* stateData;
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;
    bool gameOver;
    bool win;
    float keyTime;
    float keyTimeMax;
    float gridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    std::map<std::string, sf::Texture> textures;

    virtual void initKeybinds() = 0;

    };

#endif //DRAGHI_E_SOTTERRANEI_STATE_H