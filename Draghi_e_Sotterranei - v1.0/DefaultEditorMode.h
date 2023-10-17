//
// Created by alpacox on 29/11/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_DEFAULTEDITORMODE_H
#define DRAGHI_E_SOTTERRANEI_DEFAULTEDITORMODE_H

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;

class DefaultEditorMode : public EditorMode{
public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    ~DefaultEditorMode() override;

    void updateInput(const float& dt) override;
    void updateGui(const float& dt) override;
    void update(const float& dt) override;

    void renderGui(sf::RenderTarget& target) override;
    void render(sf::RenderTarget& target) override;

private:
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    gui::TextureSelector* textureSelector;
    sf::IntRect textureRect;
    bool collision;
    short type;
    int layer;
    bool tileAddLock;

    void initVariables();
    void initGui();

};


#endif //DRAGHI_E_SOTTERRANEI_DEFAULTEDITORMODE_H
