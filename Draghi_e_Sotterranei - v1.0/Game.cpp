//
// Created by alpacox on 30/03/21.
//

#include "precompiler.h"
#include "Game.h"

Game::Game() {
    initVariables();
    initGraphicsSettings();
    initWindow();
    initKeys();
    initStateData();
    initStates();
}

Game::~Game() {
    delete window;

    while(!states.empty()){
        delete states.top();
        states.pop();
    }
}

void Game::initVariables() {
    window = nullptr;
    dt = 0.f;
    gridSize = 32.f;
}

void Game::initGraphicsSettings() {
    gfxSettings.loadFromFile("./Config/graphics.ini");
}

void Game::initStateData() {
    stateData.windowData = window;
    stateData.gfxSettings = &gfxSettings;
    stateData.supportedKeysData = &supportedKeys;
    stateData.states = &states;
    stateData.gridSize = gridSize;
}

void Game::initWindow() {
    if(gfxSettings.fullscreen)
       window = new sf::RenderWindow(
               gfxSettings.resolution,
               gfxSettings.title,
               sf::Style::Fullscreen,
               gfxSettings.contextSettings);
    else
        window = new sf::RenderWindow(
                gfxSettings.resolution,
                gfxSettings.title,
                sf::Style::Titlebar | sf::Style::Close,
                gfxSettings.contextSettings);

    window->setFramerateLimit(gfxSettings.frameRateLimit);
}

void Game::initKeys() {
    std::ifstream ifs("./Config/supported_keys.ini");

    if (ifs.is_open()){
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value){
            supportedKeys[key] = key_value;
        }
    }

    ifs.close();

    // debug (da rimuovere)
    for (auto i : supportedKeys)
        {
            std::cout << i.first << " " << i.second << "\n";
        }
}

void Game::initStates() {
    states.push(new MainMenuState(&stateData));
}

void Game::updateDt() {
    dt = dtClock.restart().asSeconds();
}

void Game::update() {
    updateSFMLEvents();

    if(!states.empty()) {
        if(window->hasFocus()) {
            states.top()->update(this->dt);

            if (states.top()->getQuit()) {
                states.top()->endState();
                delete states.top();
                states.pop();
            }
        }
    }
    else
    {
        endApplication();
        window->close();
    }
}

void Game::render() {
    window->clear();

    if(!states.empty())
        states.top()->render();

    window->display();
}

void Game::run() {
    while (window->isOpen()){
        updateDt();
        update();
        render();
    }
}

void Game::updateSFMLEvents() {
    while (window->pollEvent(sfEvent)){
        if (sfEvent.type == sf::Event::Closed)
            window->close();
    }
}

void Game::endApplication() {
    std::cout << "Termina il gioco!" << "\n";
}

