//
// Created by alpacox on 05/10/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_EDITORSTATE_H
#define DRAGHI_E_SOTTERRANEI_EDITORSTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorModes.h"

class State;
class StateData;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class DefaultEditorMode;
class EnemyEditorMode;
class EditorStateData;

enum class EditorModes {DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE};

class EditorState : public State{
public:

    EditorState(StateData* state_data);
    ~EditorState() override;

    void updateInput(const float& dt) override;
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void updateModes(const float& dt);
    void update(const float& dt) override;

    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void renderModes(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr) override;

private:
    EditorStateData editorStateData;

    sf::View view;
    float cameraSpeed;
    sf::Font font;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*>buttons;

    TileMap* tileMap;

    std::vector<EditorMode*> modes;
    unsigned activeMode;

    void initVariables();
    void initEditorStateData();
    void initFonts();
    void initButtons();
    void initKeybinds() override;
    void initPausedMenu();
    void initGui();
    void initTileMap();
    void initView();
    void initModes();

};


#endif //DRAGHI_E_SOTTERRANEI_EDITORSTATE_H
