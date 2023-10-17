//
// Created by alpacox on 08/10/21.
//

#include "precompiler.h"
#include "SettingState.h"

SettingState::SettingState(StateData* state_data)
: State(state_data){
    initVariables();
    iniFonts();
    initKeybinds();
    initGui();
}

SettingState::~SettingState() {
    auto i = buttons.begin();
    for (i = buttons.begin(); i != buttons.end(); ++i)
        delete i->second;

    auto count = dropdownList.begin();
    for (count = dropdownList.begin(); count != dropdownList.end(); ++count)
        delete count->second;
}

void SettingState::iniFonts() {
    if(!font.loadFromFile("./Fonts/DeterminationMonoWebRegular-Z5oq.ttf"))
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void SettingState::initKeybinds() {
    std::ifstream ifs("./Config/mainmenustate_keybinds.ini");

    if (ifs.is_open()){
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
            keybinds[key] = supportedKeys->at(key2);
    }

    ifs.close();
}

void SettingState::initGui() {
    const sf::VideoMode& vm = stateData->gfxSettings->resolution;

    //Sfondo
    background.setSize(
            sf::Vector2f(
                    static_cast<float>(vm.width),
                    static_cast<float>(vm.height)
            )
    );

    if(!backgroundTexture.loadFromFile("./Resources/Images/Backgrounds/Menu001.png"))
        throw("ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");

    background.setTexture(&backgroundTexture);

    //Buttons
    buttons["BACK"] = new gui::Button(
            gui::p2pX(85.9f, vm), gui::p2pY(83.3f, vm),
            gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm),
            &font, "Back", gui::calcCharSize(vm),
            sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["APPLY"] = new gui::Button(
            gui::p2pX(70.3f, vm), gui::p2pY(83.3f, vm),
            gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm),
            &font, "Apply", gui::calcCharSize(vm),
            sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    //Modes
    std::vector<std::string> modes_str;
    for (auto &i : modes)
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));

    //DropDownList
    dropdownList["RESOLUTION"] = new gui::DropDownList(gui::p2pX(31.2f, vm), gui::p2pY(9.6f, vm),
                                                             gui::p2pX(15.6f, vm), gui::p2pY(6.9f, vm),
                                                             font, modes_str.data(), modes_str.size());

    //Text
    optionsText.setFont(font);
    optionsText.setPosition(sf::Vector2f(gui::p2pX(7.81f, vm), gui::p2pY(9.6f, vm)));
    optionsText.setCharacterSize(gui::calcCharSize(vm, 60));
    optionsText.setFillColor(sf::Color(255, 255, 255, 200));
    optionsText.setString("Resolution");
}



void SettingState::resetGui() {
/*
     * cancella gli elementi della GUI e li re-inizializza
     *
     * @return void
     */

    auto i = buttons.begin();
    for(i = buttons.begin(); i != buttons.end(); ++i)
        delete i->second;
    buttons.clear();

    auto j = dropdownList.begin();
    for(j = dropdownList.begin(); j != dropdownList.end(); ++j)
        delete j->second;
    dropdownList.clear();

    initGui();
}

void SettingState::initVariables() {
    modes = sf::VideoMode::getFullscreenModes();
}

void SettingState::update(const float& dt) {
    updateMousePosition();
    updateInput(dt);

    updateGui(dt);
}

void SettingState::updateInput(const float &dt) {

}

void SettingState::updateGui(const float &dt) {
    for (auto &i : buttons)
        i.second->update(this->mousePosWindow);

    if (buttons["BACK"]->isPressed())
        endState();

    if (buttons["APPLY"]->isPressed()){
        stateData->gfxSettings->resolution = modes[dropdownList["RESOLUTION"]->getActiveElementId()];
        window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
        resetGui();
    }

    for (auto &i : dropdownList)
        i.second->update(this->mousePosWindow, dt);
}

void SettingState::render(sf::RenderTarget* target) {
    if (!target)
        target = window;

    target->draw(background);

    renderGui(*target);

    target->draw(optionsText);

    //DEBUG commentare le seguenti linee per togliere le coordinate del mouse
    /*
    sf::Text mouseText;
    mouseText.setPosition(mousePosView.x, mousePosView.y - 50);
    mouseText.setFont(font);
    mouseText.setCharacterSize(20);
    std::stringstream  ss;
    ss << mousePosView.x << " " << mousePosView.y;
    mouseText.setString(ss.str());
    target-> draw(mouseText);
     */
    //***************************************************************************************
}

void SettingState::renderGui(sf::RenderTarget& target) {
    for (auto &i : buttons)
        i.second->render(target);

    for (auto &i : dropdownList)
        i.second->render(target);
}








