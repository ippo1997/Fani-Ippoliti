//
// Created by alpacox on 30/11/21.
//
#include "precompiler.h"
#include "EnemyEditorMode.h"

EnemyEditorMode::EnemyEditorMode(StateData *state_data, TileMap *tile_map, EditorStateData *editor_state_data)
        : EditorMode(state_data, tile_map, editor_state_data) {
    initVariables();
    initGui();
}

EnemyEditorMode::~EnemyEditorMode() {

}

void EnemyEditorMode::initGui() {

    //Testo
    cursorText.setFont(*editorStateData->font);
    cursorText.setFillColor(sf::Color::White);
    cursorText.setCharacterSize(20);
    cursorText.setPosition(editorStateData->mousePosView->x, editorStateData->mousePosView->y - 50);

    //GUI generale
    sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(stateData->gfxSettings->resolution.height)));
    sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    sidebar.setOutlineThickness(1.f);
    sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

    selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));

    selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    selectorRect.setOutlineThickness(1.f);
    selectorRect.setOutlineColor(sf::Color::Green);
}

void EnemyEditorMode::initVariables() {
    type = 0;
    amount = 1;
    timeToSpawn = 60;
    maxDistance = 100.f;
}

void EnemyEditorMode::updateInput(const float &dt) {
    //Aggiunge Tile
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeyTime()){
        if(!sidebar.getGlobalBounds().contains(sf::Vector2f(*editorStateData->mousePosWindow)))
            tileMap->addTile(editorStateData->mousePosGrid->x, editorStateData->mousePosGrid->y, 0, textureRect,
                                   type, amount, timeToSpawn, maxDistance);
    }
    //Rimuove Tile
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime()){
        if(!sidebar.getGlobalBounds().contains(sf::Vector2f(*editorStateData->mousePosWindow))) {
            tileMap->removeTile(editorStateData->mousePosGrid->x, editorStateData->mousePosGrid->y, 0, static_cast<int>(TileTypes::ENEMYSPAWNER));
        }
    }

    //TYPE UP
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds->at("TYPE_UP"))) && getKeyTime()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            if(type > 0)
                type--;
        }
        else if (type < 1000)
            type++;
        else
            type = 0;
    }
        //AMOUNT UP
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds->at("AMOUNT_UP"))) && getKeyTime()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            if(amount > 0)
                amount--;
        }
        else if (amount < 1000)
            amount++;
        else
            amount = 0;
    }
        //TIME TO SPAWN UP
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds->at("TTS_UP"))) && getKeyTime()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            if(timeToSpawn > 0)
                timeToSpawn--;
        }
        else if (timeToSpawn < 1000)
            timeToSpawn++;
        else
            timeToSpawn = 0;
    }
    //MAX DISTANCE UP
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds->at("MD_UP"))) && getKeyTime()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            if(maxDistance > 0)
                maxDistance--;
        }
        else if (maxDistance < 1000)
            maxDistance++;
        else
            maxDistance = 0;
    }
}

void EnemyEditorMode::updateGui(const float &dt) {
    selectorRect.setPosition(editorStateData->mousePosGrid->x * stateData->gridSize,
                                   editorStateData->mousePosGrid->y * stateData->gridSize);
    cursorText.setPosition(editorStateData->mousePosView->x + 100.f,
                                 editorStateData->mousePosView->y - 25.f);
    std::stringstream  ss;
    ss <<
       "\n" << "Enemy type: " << type <<
       "\n" << "Enemy amount: " << amount <<
       "\n" << "Time to spawn: " << timeToSpawn <<
       "\n" << "Max distance: " << maxDistance;

    cursorText.setString(ss.str());
}

void EnemyEditorMode::update(const float &dt) {
    updateInput(dt);
    updateGui(dt);
}

void EnemyEditorMode::renderGui(sf::RenderTarget &target) {
    target.setView(*editorStateData->view);
    target.draw(selectorRect);
    target.draw(cursorText);

    target.setView(target.getDefaultView());
    target.draw(sidebar);
}

void EnemyEditorMode::render(sf::RenderTarget &target) {
    renderGui(target);
}

int EnemyEditorMode::getType() const{
    return type;
}
