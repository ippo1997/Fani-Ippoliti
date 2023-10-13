//
// Created by alpacox on 29/11/21.
//

#include "precompiler.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData *state_data, TileMap* tile_map, EditorStateData* editor_state_data)
:stateData(state_data), tileMap(tile_map), editorStateData(editor_state_data){

}

EditorMode::~EditorMode() {

}

bool EditorMode::getKeyTime() {
    if(*editorStateData->keyTime >= *editorStateData->keyTimeMax){
        *editorStateData->keyTime = 0.f;
        return true;
    }
    return false;
}
