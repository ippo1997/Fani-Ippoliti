//
// Created by alpacox on 29/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_EDITORMODE_H
#define DRAGHI_E_SOTTERRANEI_EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class State;
class StateData;
class TileMap;
class Tile;

class EditorStateData {
public:
    EditorStateData() {};

    sf::View *view;
    sf::Font *font;

    float *keyTime;
    float *keyTimeMax;

    std::map<std::string, int> *keybinds;

    sf::Vector2i *mousePosScreen;
    sf::Vector2i *mousePosWindow;
    sf::Vector2f *mousePosView;
    sf::Vector2i *mousePosGrid;
};

class EditorMode {
public:
    EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EditorMode();

    bool getKeyTime();

    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual void update(const float& dt) = 0;

    virtual void renderGui(sf::RenderTarget& target) = 0;
    virtual void render(sf::RenderTarget& target) = 0;

protected:
    StateData* stateData;
    EditorStateData* editorStateData;
    TileMap* tileMap;

};


#endif //DRAGHI_E_SOTTERRANEI_EDITORMODE_H
