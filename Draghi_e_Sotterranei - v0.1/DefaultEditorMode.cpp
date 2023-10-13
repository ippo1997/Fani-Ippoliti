//
// Created by alpacox on 29/11/21.
//

#include "DefaultEditorMode.h"

DefaultEditorMode::DefaultEditorMode(StateData *state_data, TileMap* tile_map, EditorStateData* editor_state_data)
: EditorMode(state_data, tile_map, editor_state_data) {
    initVariables();
    initGui();
}

DefaultEditorMode::~DefaultEditorMode() {
    delete textureSelector;
}

void DefaultEditorMode::initVariables() {
    textureRect = sf::IntRect(0, 0, static_cast<int>(stateData->gridSize), static_cast<int>(stateData->gridSize));
    collision = false;
    type = static_cast<int>(TileTypes::DEFAULT);
    layer = 0;
    tileAddLock = false;
}

void DefaultEditorMode::initGui() {
    //Testo
    cursorText.setFont(*editorStateData->font);
    cursorText.setFillColor(sf::Color::White);
    cursorText.setCharacterSize(20);
    cursorText.setPosition(editorStateData->mousePosView->x, editorStateData->mousePosView->y - 50);

    //GUI
    sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(stateData->gfxSettings->resolution.height)));
    sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    sidebar.setOutlineThickness(1.f);
    sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

    selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));

    selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    selectorRect.setOutlineThickness(1.f);
    selectorRect.setOutlineColor(sf::Color::Green);

    selectorRect.setTexture(tileMap->getTileSheet());
    selectorRect.setTextureRect(textureRect);

    /** Modifica dimensioni texture selector **/
    textureSelector = new gui::TextureSelector(60.f, 20.f, 448.f, 416.f,
                                                     stateData->gridSize, tileMap->getTileSheet(),
                                                     *editorStateData->font, "TS");
}

void DefaultEditorMode::updateInput(const float &dt) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()){
        if(!sidebar.getGlobalBounds().contains(sf::Vector2f(*editorStateData->mousePosWindow))) {
            if (!textureSelector->getActive() ) {
                if(tileAddLock){
                    if(tileMap->tileEmpty(editorStateData->mousePosGrid->x, editorStateData->mousePosGrid->y, 0))
                        tileMap->addTile(editorStateData->mousePosGrid->x, editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
                }
                else
                    this->tileMap->addTile(editorStateData->mousePosGrid->x, editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
            } else
                textureRect = textureSelector->getTextureRect();
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime()){
        if(!sidebar.getGlobalBounds().contains(sf::Vector2f(*editorStateData->mousePosWindow))) {
            if (!textureSelector->getActive())
                tileMap->removeTile(editorStateData->mousePosGrid->x, editorStateData->mousePosGrid->y, 0);
        }
    }
    //TOGGLE COLLISION
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds->at("TOGGLE_COLLISION"))) && getKeyTime()){
        if (collision)
            collision = false;
        else
            collision = true;
    }
    //INCREASE TYPE
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds->at("INCREASE_TYPE"))) && getKeyTime()){
        if(type < 2)
            ++type;
    }
    //DECREASE TYPE
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds->at("DECREASE_TYPE"))) && getKeyTime()){
        if(type > 0)
            --type;
    }
    //TOGGLE TYPE LOCK
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds->at("TOGGLE_TILE_LOCK"))) && getKeyTime()){
        if(tileAddLock)
            tileAddLock = false;
        else
            tileAddLock = true;
    }
}

void DefaultEditorMode::updateGui(const float &dt) {
    textureSelector->update(*editorStateData->mousePosWindow, dt);

    if(!textureSelector->getActive()) {
        selectorRect.setTextureRect(textureRect);
        selectorRect.setPosition(editorStateData->mousePosGrid->x * stateData->gridSize,
                                       editorStateData->mousePosGrid->y * stateData->gridSize);
    }

    cursorText.setPosition(editorStateData->mousePosView->x + 100.f, editorStateData->mousePosView->y - 25.f);
    std::stringstream  ss;
    ss << editorStateData->mousePosView->x << " " << editorStateData->mousePosView->y <<
       "\n" << editorStateData->mousePosGrid->x << " " << editorStateData->mousePosGrid->y <<
       "\n" << textureRect.left << " " << textureRect.top <<
       "\n" << "Collision: " << collision <<
       "\n" << "Type: " << type <<
       "\n" << "Tiles: " << tileMap->getLayerSize(editorStateData->mousePosGrid->x, editorStateData->mousePosGrid->y, this->layer) <<
       "\n" << "Tile lock: " << tileAddLock;
    cursorText.setString(ss.str());
}

void DefaultEditorMode::update(const float &dt) {
    updateInput(dt);
    updateGui(dt);
}

void DefaultEditorMode::renderGui(sf::RenderTarget &target) {
    if(!textureSelector->getActive()) {
        target.setView(*editorStateData->view);
        target.draw(selectorRect);
    }

    target.setView(stateData->windowData->getDefaultView());
    textureSelector->render(target);
    target.draw(sidebar);

    target.setView(*editorStateData->view);
    target.draw(cursorText);
}

void DefaultEditorMode::render(sf::RenderTarget &target) {
    this->renderGui(target);
}




