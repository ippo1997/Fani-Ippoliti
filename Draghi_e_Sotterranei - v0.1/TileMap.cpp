//
// Created by alpacox on 25/03/21.
//

#include "precompiler.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, int  width, int  height, std::string texture_file) {
    gridSizeF = gridSize;
    gridSizeI = static_cast<int>(this->gridSizeF);
    maxSizeWorldGrid.x = width;
    maxSizeWorldGrid.y = height;
    maxSizeWorldF.x = static_cast<float>(width) * gridSize;
    maxSizeWorldF.y = static_cast<float>(height) * gridSize;
    layers = 1; //layers<>layer
    textureFile = texture_file;
    fromX = 0;
    toX = 0;
    fromY = 0;
    toY = 0;
    layer = 0; //layer<>layers

    map.resize(maxSizeWorldGrid.x, std::vector< std::vector< std::vector< Tile*> > >());
    for(int x = 0; x < maxSizeWorldGrid.x; x++){
        for(int y = 0; y < maxSizeWorldGrid.y; y++) {
            map[x].resize(maxSizeWorldGrid.y, std::vector< std::vector < Tile*> >());
            for (int z = 0; z < layers; z++)
                map[x][y].resize(layers, std::vector<Tile*>());
        }
    }
    if(!tileSheet.loadFromFile(textureFile))
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file <<"\n";

    collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    collisionBox.setOutlineColor(sf::Color::Red);
    collisionBox.setOutlineThickness(-1.f);
}

TileMap::TileMap(const std::string file_name) {
    fromX = 0;
    toX = 0;
    fromY = 0;
    toY = 0;
    layer = 0; //layer<>layers

    loadFromFile(file_name);

    collisionBox.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    collisionBox.setOutlineColor(sf::Color::Red);
    collisionBox.setOutlineThickness(-1.f);
}

TileMap::~TileMap() {
    clear();
}

void TileMap::clear() {
    if(!map.empty()) {
        for (int x = 0; x < map.size(); x++) {
            for (int y = 0; y < map[x].size(); y++) {
                for (int z = 0; z < map[x][y].size(); z++) {
                    for (int k = 0; k < map[x][y][z].size(); k++) {
                        delete map[x][y][z][k];
                        map[x][y][z][k] = nullptr;
                    }
                    map[x][y][z].clear();
                }
                map[x][y].clear();
            }
            map[x].clear();
        }
        map.clear();
    }
    //std::cout << this->map.size() << "\n"; //debug
}

bool TileMap::tileEmpty(const int x, const int y, const int z) const{
    if(x >= 0 && x < maxSizeWorldGrid.x &&
       y >= 0 && y < maxSizeWorldGrid.y &&
       z >= 0 && z < layers)
        return map[x][y][z].empty();
    return false;
}

const sf::Texture *TileMap::getTileSheet() const{
    return &tileSheet;
}

int TileMap::getLayerSize(const int x, const int y, const int layer) const{
    if(x >= 0 && x <static_cast<int>(map.size())){
        if(y >= 0 && y <static_cast<int>(map[x].size())){
            if(layer >= 0 && layer <static_cast<int>(map[x][y].size())){
                return map[x][y][layer].size();
            }
        }
    }
    return -1;
}

const sf::Vector2f &TileMap::getMaxSizeF() const {
    return maxSizeWorldF;
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type) {
    if(x < maxSizeWorldGrid.x && x >= 0 &&
       y < maxSizeWorldGrid.y && y >= 0 &&
       z < layers && z >= 0){

        map[x][y][z].push_back(new RegularTile(type, x, y, this->gridSizeF, tileSheet, texture_rect, collision));

        //std::cout <<"DEBUG: ADDED A TILE!" << "\n"; //debug
    }
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect &texture_rect,
                      const int enemy_type, const int enemy_amount, const int enemy_tts, const int enemy_md) {

    if(x < maxSizeWorldGrid.x && x >= 0 &&
       y < maxSizeWorldGrid.y && y >= 0 &&
       z < layers && z >= 0){

        map[x][y][z].push_back(new EnemySpawnerTile(x, y, this->gridSizeF, this->tileSheet, texture_rect,
                                                          enemy_type, enemy_amount, enemy_tts, enemy_md));
    }
}

void TileMap::removeTile(const int x, const int y, const int z, const int type) {
    if(x < maxSizeWorldGrid.x && x >= 0 &&
       y < maxSizeWorldGrid.y && y >= 0 &&
       z < layers && z >= 0){
        if(!map[x][y][z].empty()){
            if(type >= 0){
                if(map[x][y][z].back()->getType() == type) {
                    delete map[x][y][z][map[x][y][z].size() - 1];
                    map[x][y][z].pop_back();
                    //std::cout << "DEBUG: REMOVED A TILE!" << "\n"; //debug
                }
            }
            else{
                delete map[x][y][z][map[x][y][z].size()-1];
                map[x][y][z].pop_back();
                //std::cout <<"DEBUG: REMOVED A TILE!" << "\n"; //debug
            }
        }
    }
}

void TileMap::saveToFile(const std::string file_name) {
    /*Salva tilemap in un file di testo
    * Format:
    * Basic:
    * Size x y
    * gridSize
    * layers
    * texture file
    *
    * All tiles:
    * type
    * gridPos x y layer
    * Texture rect x y
    * collision
    * tile_specific..
    */

    std::ofstream out_file;

    out_file.open(file_name);

    if(out_file.is_open()){

        out_file << maxSizeWorldGrid.x << " " << maxSizeWorldGrid.y << "\n"
                 << gridSizeI << "\n"
                 << layers << "\n"
                 << textureFile << "\n";

        for(int x = 0; x < maxSizeWorldGrid.x; x++){
            for(int y = 0; y < maxSizeWorldGrid.y; y++) {
                for (int z = 0; z < layers; z++) {
                    if(!map[x][y][z].empty()) {
                        for(int k = 0; k < map[x][y][z].size(); k++){
                            out_file << x << " " << y << " " << z << " " <<
                                     map[x][y][z][k]->getAsString()
                                     << " ";
                        }
                    }
                }
            }
        }
    }
    else{
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE " << file_name << "\n";
    }

    out_file.close();
}

void TileMap::loadFromFile(const std::string file_name) {
    std::ifstream in_file;

    in_file.open(file_name);

    if(in_file.is_open()){
        sf::Vector2i  size;
        int gridSize = 0;
        int layers = 0;
        std::string texture_file = "";
        int x = 0;
        int y = 0;
        int z = 0;
        int trX = 0;
        int trY = 0;
        bool collision = false;
        short type = 0;

        in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

        gridSizeF = static_cast<float>(gridSize);
        gridSizeI = gridSize;
        maxSizeWorldGrid.x = size.x;
        maxSizeWorldGrid.y = size.y;
        maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
        maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
        this->layers = layers;
        textureFile = texture_file;

        clear();

        map.resize(maxSizeWorldGrid.x, std::vector< std::vector< std::vector< Tile*> > >());
        for(int x = 0; x < maxSizeWorldGrid.x; x++){
            for(int y = 0; y < maxSizeWorldGrid.y; y++) {
                map[x].resize(maxSizeWorldGrid.y, std::vector< std::vector< Tile*> >());
                for (int z = 0; z < this->layers; z++) {
                    map[x][y].resize(this->layers, std::vector< Tile*>());
                }
            }
        }
        if(!tileSheet.loadFromFile(textureFile))
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file <<"\n";

        while(in_file >> x >> y >> z >> type){
          if(type == static_cast<int>(TileTypes::ENEMYSPAWNER)){
              //amount, time to spawn, max distance
              int enemy_type = 0;
              int enemy_am = 0;
              int enemy_tts = 0;
              int enemy_md = 0;

              in_file >> trX >> trY >> enemy_type >> enemy_am >> enemy_tts >> enemy_md;

              map[x][y][z].push_back(
                      new EnemySpawnerTile(
                              x, y,
                              this->gridSizeF,
                              this->tileSheet,
                              sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
                              enemy_type,
                              enemy_am,
                              enemy_tts,
                              enemy_md
                      )
              );

          }
          else{
              in_file >> trX >> trY >> collision;

              map[x][y][z].push_back(new RegularTile(
                                                   type,
                                                   x, y,
                                                   this->gridSizeF,
                                                   this->tileSheet,
                                                   sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
                                                   collision
                                           )
              );
          }
        }
    }
    else{
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE " << file_name << "\n";
    }

    in_file.close();
}

void TileMap::updateWorldBoundsCollision(GameCharacter *gameCharacter, const float &dt) {

    //Limiti mappa

    if(gameCharacter->getPosition().x < 0.f) {
        gameCharacter->setPosition(0.f, gameCharacter->getPosition().y);
        gameCharacter->stopVelocityX();
    }
    else if(gameCharacter->getPosition().x + gameCharacter->getGlobalBounds().width > maxSizeWorldF.x) {
        gameCharacter->setPosition(maxSizeWorldF.x - gameCharacter->getGlobalBounds().width, gameCharacter->getPosition().y);
        gameCharacter->stopVelocityX();
    }
    if(gameCharacter->getPosition().y < 0.f) {
        gameCharacter->setPosition(gameCharacter->getPosition().x, 0.f);
        gameCharacter->stopVelocityY();
    }
    else if(gameCharacter->getPosition().y + gameCharacter->getGlobalBounds().height > maxSizeWorldF.y) {
        gameCharacter->setPosition( gameCharacter->getPosition().x, maxSizeWorldF.y - gameCharacter->getGlobalBounds().height);
        gameCharacter->stopVelocityY();
    }
}

void TileMap::updateTileCollision(GameCharacter *gameCharacter, const float &dt) {

    //Tiles
    layer = 0;

    fromX = gameCharacter->getGridPosition(this->gridSizeI).x - 1;
    if(fromX < 0)
        fromX = 0;
    else if(fromX > maxSizeWorldGrid.x)
        fromX = maxSizeWorldGrid.x;

    toX = gameCharacter->getGridPosition(this->gridSizeI).x + 3;
    if(toX < 0)
        toX = 0;
    else if(toX > maxSizeWorldGrid.x)
        toX = maxSizeWorldGrid.x;

    fromY = gameCharacter->getGridPosition(this->gridSizeI).y - 1;
    if(fromY < 0)
        fromY = 0;
    else if(fromY > maxSizeWorldGrid.y)
        fromY = maxSizeWorldGrid.y;

    toY = gameCharacter->getGridPosition(this->gridSizeI).y + 3;
    if(toY < 0)
        toY = 0;
    else if(toY > maxSizeWorldGrid.y)
        toY = maxSizeWorldGrid.y;

    //Collisioni
    for(int x = fromX; x < toX; x++){
        for(int y = fromY; y < toY; y++) {
            for (int k = 0; k < map[x][y][this->layer].size(); k++) {

                sf::FloatRect heroBounds = gameCharacter->getGlobalBounds();
                sf::FloatRect wallBounds = map[x][y][layer][k]->getGlobalBounds();
                sf::FloatRect nextPositionBounds = gameCharacter->getNextPositionBounds(dt);

                if (map[x][y][layer][k]->getCollision() &&
                    map[x][y][layer][k]->intersects(nextPositionBounds)) {

                    //Collisione inferiore
                    if (heroBounds.top < wallBounds.top
                        && heroBounds.top + heroBounds.height < wallBounds.top + wallBounds.height
                        && heroBounds.left < wallBounds.left + wallBounds.width
                        && heroBounds.left + heroBounds.width > wallBounds.left
                            ) {
                        gameCharacter->stopVelocityY();
                        gameCharacter->setPosition(heroBounds.left, wallBounds.top - heroBounds.height);
                    }
                        //Collisione superiore
                    else if (heroBounds.top > wallBounds.top
                             && heroBounds.top + heroBounds.height > wallBounds.top + wallBounds.height
                             && heroBounds.left < wallBounds.left + wallBounds.width
                             && heroBounds.left + heroBounds.width > wallBounds.left
                            ) {
                        gameCharacter->stopVelocityY();
                        gameCharacter->setPosition(heroBounds.left, wallBounds.top + wallBounds.height);
                    }

                    //Collisione destra
                    if (heroBounds.left < wallBounds.left
                        && heroBounds.left + heroBounds.width < wallBounds.left + wallBounds.width
                        && heroBounds.top < wallBounds.top + wallBounds.height
                        && heroBounds.top + heroBounds.height > wallBounds.top) {
                        gameCharacter->stopVelocityX();
                        gameCharacter->setPosition(wallBounds.left - heroBounds.width, heroBounds.top);
                    }
                        //Collisione sinistra
                    else if (heroBounds.left > wallBounds.left
                             && heroBounds.left + heroBounds.width > wallBounds.left + wallBounds.width
                             && heroBounds.top < wallBounds.top + wallBounds.height
                             && heroBounds.top + heroBounds.height > wallBounds.top
                            ) {
                        gameCharacter->stopVelocityX();
                        gameCharacter->setPosition(wallBounds.left + wallBounds.width, heroBounds.top);
                    }
                }
            }
        }
    }
}

void TileMap::updateTiles(GameCharacter *gameCharacter, const float &dt,
                          EnemyFactory &enemyStrategy) {
    //Tiles
    layer = 0;

    fromX = gameCharacter->getGridPosition(this->gridSizeI).x - 20;
    if(fromX < 0)
        fromX = 0;
    else if(fromX > maxSizeWorldGrid.x)
        fromX = maxSizeWorldGrid.x;

    toX = gameCharacter->getGridPosition(this->gridSizeI).x + 21;
    if(toX < 0)
        toX = 0;
    else if(toX > maxSizeWorldGrid.x)
        toX = maxSizeWorldGrid.x;

    fromY = gameCharacter->getGridPosition(this->gridSizeI).y - 11;
    if(fromY < 0)
        fromY = 0;
    else if(fromY > maxSizeWorldGrid.y)
        fromY = maxSizeWorldGrid.y;

    toY = gameCharacter->getGridPosition(this->gridSizeI).y + 12;
    if(toY < 0)
        toY = 0;
    else if(toY > maxSizeWorldGrid.y)
        toY = maxSizeWorldGrid.y;

    //Collisioni
    for(int x = fromX; x < toX; x++){
        for(int y = fromY; y < toY; y++) {
            for (int k = 0; k < map[x][y][layer].size(); k++) {

                map[x][y][layer][k]->update();

                if(map[x][y][layer][k]->getType() == static_cast<int>(TileTypes::ENEMYSPAWNER)){
                    EnemySpawnerTile* es = dynamic_cast<EnemySpawnerTile*>(map[x][y][layer][k]);
                    if(es) {
                        if (es->getSpawnTimer() && es->getEnemyCounter() < es->getEnemyAmount()) {
                            enemyStrategy.createEnemy(es->getEnemyType(), x * gridSizeF, y * gridSizeF, *es);
                            std::cout << "Spawned!" << "\n"; //debug
                        }
                    }
                }
            }
        }
    }
}

void TileMap::update(GameCharacter *gameCharacter, const float& dt) {

}

void TileMap::render(
        sf::RenderTarget &target,
        const sf::Vector2i& gridPosition,
        sf::Shader* shader,
        const sf::Vector2f heroPosition,
        const bool show_collision
        ) {

        layer = 0;

        fromX = gridPosition.x - 20;
        if (fromX < 0)
            fromX = 0;
        else if (fromX > maxSizeWorldGrid.x)
            fromX = maxSizeWorldGrid.x;

        toX = gridPosition.x + 21;
        if (toX < 0)
            toX = 0;
        else if (toX > maxSizeWorldGrid.x)
            toX = maxSizeWorldGrid.x;

        fromY = gridPosition.y - 11;
        if (fromY < 0)
            fromY = 0;
        else if (fromY > maxSizeWorldGrid.y)
            fromY = maxSizeWorldGrid.y;

        toY = gridPosition.y + 12;
        if (toY < 0)
            toY = 0;
        else if (toY > maxSizeWorldGrid.y)
            toY = maxSizeWorldGrid.y;

        for (int x = fromX; x < toX; x++) {
            for (int y = fromY; y < toY; y++) {
                for (int k = 0; k < map[x][y][layer].size(); k++){
                    if(map[x][y][layer][k]->getType() == static_cast<int>(TileTypes::FLAVOUR)){
                        deferredRenderStack.push(map[x][y][layer][k]);
                    }
                    else{
                        if(shader)
                            map[x][y][layer][k]->render(target, shader, heroPosition);
                        else
                            map[x][y][layer][k]->render(target);

                    }
                    if(show_collision){
                        if (map[x][y][layer][k]->getCollision()) {
                            collisionBox.setPosition(map[x][y][layer][k]->getPosition());
                            target.draw(collisionBox);
                        }
                        if(map[x][y][layer][k]->getType() == static_cast<int>(TileTypes::ENEMYSPAWNER)){
                            collisionBox.setPosition(map[x][y][layer][k]->getPosition());
                            target.draw(collisionBox); /// commentare per visualizzare o no enemySpawner
                        }
                    }
                }
            }
        }
}

void TileMap::renderDeferred(sf::RenderTarget &target, sf::Shader* shader, const sf::Vector2f heroPosition) {
    while(!deferredRenderStack.empty()){
        if(shader)
            deferredRenderStack.top()->render(target, shader, heroPosition);
        else
            deferredRenderStack.top()->render(target);

        deferredRenderStack.pop();
    }
}
