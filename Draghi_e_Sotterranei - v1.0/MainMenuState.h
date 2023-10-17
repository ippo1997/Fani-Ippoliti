//
// Created by alpacox on 27/09/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_MAINMENUSTATE_H
#define DRAGHI_E_SOTTERRANEI_MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingState.h"
#include "Gui.h"

class MainMenuState : public State {

public:
    explicit MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    void updateInput(const float& dt) override;
    void updateGui();
    void update(const float& dt) override;
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr) override;


private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    sf::RectangleShape btnBackground;
    std::map<std::string, gui::Button*>buttons;

    void initVariables();
    void iniFonts();
    void initGui();
    void initKeybinds() override;
    void resetGui();

};



#endif //DRAGHI_E_SOTTERRANEI_MAINMENUSTATE_H
