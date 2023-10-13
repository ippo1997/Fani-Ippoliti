//
// Created by alpacox on 05/10/21.
//

#include "precompiler.h"
#include "EditorState.h"

EditorState::EditorState(StateData* state_data)
        : State(state_data)
{
    this->initVariables();
    this->initEditorStateData();
    this->initView();
    this->initFonts();
    this->initKeybinds();
    this->initPausedMenu();
    this->initButtons();
    this->initTileMap();
    this->initGui();
    this->initModes();
}

EditorState::~EditorState() {
    auto i = buttons.begin();
    for (i = buttons.begin(); i != buttons.end(); ++i)
        delete i->second;
    delete pmenu;
    delete tileMap;

    for(size_t i = 0; i < modes.size(); i++){
        delete modes[i];
    }
}

void EditorState::initVariables() {
    cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData() {
    editorStateData.view = &view;
    editorStateData.font = &font;
    editorStateData.keyTime = &keyTime;
    editorStateData.keyTimeMax = &keyTimeMax;
    editorStateData.keybinds = &keybinds;
    editorStateData.mousePosGrid = &mousePosGrid;
    editorStateData.mousePosScreen = &mousePosScreen;
    editorStateData.mousePosView = &mousePosView;
    editorStateData.mousePosWindow = &mousePosWindow;
}

void EditorState::initFonts() {
    if(!font.loadFromFile("./Fonts/DeterminationMonoWebRegular-Z5oq.ttf"))
        throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
}

void EditorState::initButtons() {

}

void EditorState::initKeybinds() {
    std::ifstream ifs("./Config/editorstate_keybinds.ini");

    if (ifs.is_open()){
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2){
            keybinds[key] = supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void EditorState::initPausedMenu() {
    const sf::VideoMode& vm = stateData->gfxSettings->resolution;
    pmenu = new PauseMenu(stateData->gfxSettings->resolution, this->font, PauseTypes::PAUSE_STATE);

    pmenu->addButton("QUIT", gui::p2pY(62.5f, vm)/*450.f*/, gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm), gui::calcCharSize(vm), "Quit");
    pmenu->addButton("SAVE", gui::p2pY(48.6f, vm)/*350.f*/, gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm), gui::calcCharSize(vm), "Save");
    pmenu->addButton("LOAD", gui::p2pY(34.7f, vm)/*250.f*/, gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm), gui::calcCharSize(vm), "Load");
}

void EditorState::initGui() {

}

void EditorState::initTileMap() {
    tileMap = new TileMap(stateData->gridSize, 100, 100,"./Resources/Images/Tiles/TileSet1.png");
}

void EditorState::initView() {
    view.setSize(sf::Vector2f(static_cast<float>(stateData->gfxSettings->resolution.width), static_cast<float>(stateData->gfxSettings->resolution.height)));
    view.setCenter(static_cast<float>(stateData->gfxSettings->resolution.width) / 2.f, static_cast<float>(stateData->gfxSettings->resolution.height) / 2.f);
}

void EditorState::initModes() {
    modes.push_back(new DefaultEditorMode(stateData, tileMap, &editorStateData));
    modes.push_back(new EnemyEditorMode(stateData, tileMap, &editorStateData));
    activeMode = static_cast<unsigned int>(EditorModes::DEFAULT_EDITOR_MODE);
}

void EditorState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeyTime()){
        if(!paused)
            pauseState();
        else
            unpauseState();
    }
}

void EditorState::updateEditorInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_UP")))){
        view.move(0.f, -std::floor(cameraSpeed * dt)); //valore regola velocità scorrimento schermo
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_DOWN")))){
        view.move(0.f, std::floor(cameraSpeed * dt)); //valore regola velocità scorrimento schermo
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_LEFT")))){
        view.move(-std::floor(cameraSpeed * dt), 0.f); //valore regola velocità scorrimento schermo
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_RIGHT")))){
        view.move(std::floor(cameraSpeed * dt), 0.f); //valore regola velocità scorrimento schermo
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MODE_UP")))){
        if(activeMode < modes.size() - 1){
            activeMode++;
        }
        else {
            std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE  UP!" << "\n";
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MODE_DOWN")))){
        if(activeMode > 0){
            activeMode--;
        }
        else {
            std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE DOWN!" << "\n";
        }
    }
}

void EditorState::updateButtons() {
    for (auto &i : buttons)
        i.second->update(this->mousePosWindow);
}

void EditorState::updateGui(const float& dt) {

}

void EditorState::updatePauseMenuButtons() {
    if(pmenu->isButtonPressed("QUIT"))
        endState();

    if(pmenu->isButtonPressed("SAVE"))
        tileMap->saveToFile("./saves_file.txt");

    if(pmenu->isButtonPressed("LOAD"))
        tileMap->loadFromFile("./saves_file.txt");
}

void EditorState::updateModes(const float& dt) {
    modes[activeMode]->update(dt);
}

void EditorState::update(const float& dt) {
    updateMousePosition(&view);
    updateKeyTime(dt);
    updateInput(dt);

    if(!paused){
        updateButtons();
        updateGui(dt);
        updateEditorInput(dt);
        updateModes(dt);
    }
    else{
        pmenu->update(this->mousePosWindow);
        updatePauseMenuButtons();
    }
}

void EditorState::renderButtons(sf::RenderTarget& target) {
    for (auto &i : buttons){
        i.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget &target) {

}

void EditorState::renderModes(sf::RenderTarget& target) {

    modes[activeMode]->render(target);

}

void EditorState::render(sf::RenderTarget* target) {
    if (!target)
        target = window;

    target->setView(view);
    tileMap->render(*target, mousePosGrid, nullptr, sf::Vector2f(), true);
    tileMap->renderDeferred(*target);

    target->setView(window->getDefaultView());
    renderButtons(*target);

    renderGui(*target);

    renderModes(*target);

    if(paused){
        target->setView(window->getDefaultView());
        pmenu->render(*target);
    }
}
