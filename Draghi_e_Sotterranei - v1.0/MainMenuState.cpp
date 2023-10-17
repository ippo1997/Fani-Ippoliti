//
// Created by alpacox on 27/09/21.
//

#include "precompiler.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData* state_data)
        : State(state_data)
{
    initVariables();
    iniFonts();
    initKeybinds();
    initGui();
    resetGui();
}

MainMenuState::~MainMenuState() {

    auto i = buttons.begin();
    for (i = buttons.begin(); i != buttons.end(); ++i)
        delete i->second;
}

void MainMenuState::render(sf::RenderTarget* target) {

    if (!target)
        target = window;

    target->draw(background);

    target->draw(btnBackground);

    renderButtons(*target);

    //DA COMMENTARE SUCCESSIVAMENTE (fatto): Aiuta a trovare le coordinate sullo schermo per posizionare cose
    /*
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(20);
    std::stringstream  ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());

    target-> draw(mouseText);
     */
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}


void MainMenuState::updateInput(const float &dt) {

}

void MainMenuState::update(const float& dt) {

    updateMousePosition();
    updateInput(dt);

    updateGui();
}

void MainMenuState::iniFonts() {

    if(!font.loadFromFile("./Fonts/DeterminationMonoWebRegular-Z5oq.ttf")){
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }

}

void MainMenuState::initKeybinds() {

    std::ifstream ifs("./Config/mainmenustate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
            keybinds[key] = supportedKeys->at(key2);
    }

    ifs.close();
}

void MainMenuState::initGui() {

    const sf::VideoMode& vm = stateData->gfxSettings->resolution;

//Background
    background.setSize(
            sf::Vector2f(
                    static_cast<float>(vm.width),
                    static_cast<float>(vm.height)
            )
    );

    if(!backgroundTexture.loadFromFile("./Resources/Images/Backgrounds/Menu002.png")){
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    background.setTexture(&backgroundTexture);

    //Button Background
    btnBackground.setSize(
            sf::Vector2f(
                    static_cast<float>(vm.width / 5),
                    static_cast<float>(vm.height)
                    )
            );
    btnBackground.setPosition(gui::p2pX(5.5, vm), gui::p2pY(40.5, vm));
    btnBackground.setFillColor(sf::Color(10, 10, 10, 100));

    //Buttons
    buttons["GAME_STATE"] = new gui::Button(
            gui::p2pX(7.81f, vm), gui::p2pY(41.6f, vm),
            gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm),
            &font, "New Game", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["SETTINGS_STATE"] = new gui::Button(
            gui::p2pX(7.81f, vm), gui::p2pY(55.5f, vm),
            gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm),
            &font, "Settings", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["EDITOR_STATE"] = new gui::Button(
            gui::p2pX(7.81f, vm), gui::p2pY(69.4f, vm),
            gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm),
            &font, "Editor", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["EXIT_STATE"] = new gui::Button(
            gui::p2pX(7.81f, vm), gui::p2pY(83.3f, vm),
            gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm),
            &font, "Quit", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::resetGui() {
    /*
     * cancella gli elementi della GUI e li re-inizializza
     *
     * @return void
     */

    auto i = buttons.begin();
    for (i = buttons.begin(); i != buttons.end(); ++i)
    {
        delete i->second;
    }
    buttons.clear();

    initGui();

}

void MainMenuState::updateGui() {

    for (auto &i : buttons)
        i.second->update(this->mousePosWindow);

    if (buttons["GAME_STATE"]->isPressed())
        states->push(new GameState(this->stateData));

    if (this->buttons["SETTINGS_STATE"]->isPressed())
        states->push(new SettingState(this->stateData));

    if (this->buttons["EDITOR_STATE"]->isPressed())
        states->push(new EditorState(this->stateData));

    if (this->buttons["EXIT_STATE"]->isPressed())
        endState();
}

void MainMenuState::renderButtons(sf::RenderTarget& target) {
    for (auto &i : buttons)
        i.second->render(target);
}

void MainMenuState::initVariables() {

}


