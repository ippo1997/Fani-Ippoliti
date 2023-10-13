//
// Created by alpacox on 26/03/21.
//

#include "precompiler.h"
#include "GameState.h"

GameState::GameState(StateData* state_data)
    : State(state_data) {
    initDeferredRender();
    initView();
    initKeybinds();
    initFonts();
    initTextures();
    initPausedMenu();
    initGameOverState();
    initWinState();
    initShaders();
    initKeyTime();
    initDebugText();

    initHeroes();
    initHeroGUI();
    initEnemyStrategy();
    initTileMap();
    initSystems();

    initAchievements();

    gameManager->CreateMessage("\nWELCOME!\n");
    tts->addTextTag(TagTypes::ACHIEVEMENT_TAG, 100, 100, 1, "Achievement unlocked: +", "\nWELCOME!");
}

GameState::~GameState() {
    delete pmenu;
    delete gameOverMenu;
    delete winMenu;
    delete hero;
    delete heroGUI;
    delete enemyStrategy;
    delete tileMap;
    delete tts;

    for(size_t i = 0; i < activeEnemies.size(); i++){
        delete activeEnemies[i];
    }

    delete achievements;
    delete gameManager;
}

void GameState::initView() {
    view.setSize(
            sf::Vector2f(
                    static_cast<float>(stateData->gfxSettings->resolution.width / 2),
                    static_cast<float>(stateData->gfxSettings->resolution.height / 2)
            )
    );

    view.setCenter(
            sf::Vector2f(
                    static_cast<float>(stateData->gfxSettings->resolution.width) / 2.f,
                    static_cast<float>(stateData->gfxSettings->resolution.height) / 2.f
            )
    );
}

void GameState::initKeyTime() {
    keyTimeMax = 0.3f;
    keyTimer.restart();
}

void GameState::initDebugText() {
    debugText.setFont(font);
    debugText.setFillColor(sf::Color::White);
    debugText.setCharacterSize(16);
    debugText.setPosition(15.f,window->getSize().y / 2.f);
}

void GameState::initKeybinds() {
    std::ifstream ifs("./Config/gamestate_keybinds.ini");

    if (ifs.is_open()){
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
            keybinds[key] = supportedKeys->at(key2);
    }
    ifs.close();
}

void GameState::initFonts() {
    if(!font.loadFromFile("./Fonts/DeterminationMonoWebRegular-Z5oq.ttf"))
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void GameState::initTextures() {
    if (!textures["HERO_SHEET"].loadFromFile("./Resources/Images/Sprites/Hero/Woodcutter_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HERO_TEXTURE";
    }
    if (!textures["MUMMY_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Mummy/Mummy_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MUMMY_TEXTURE";
    }
    if (!textures["SCORPION_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Scorpio/Scorpio_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SCORPION_TEXTURE";
    }
    if (!textures["HYENA_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Hyena/Hyena_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HYENA_TEXTURE";
    }
    if (!textures["SNAKE_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Snake/Snake_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SNAKE_TEXTURE";
    }
    if (!textures["VULTURE_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Vulture/Vulture_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_VULTURE_TEXTURE";
    }
    if (!textures["DECEASED_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Deceased/Deceased_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_DECEASED_TEXTURE";
    }
    if (!textures["CENTIPEDE_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Centipede/Centipede_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_CENTIPEDE_TEXTURE";
    }
    if (!textures["BIG_BLOATED_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Big bloated/BigBloated_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIG_BLOATED_TEXTURE";
    }
    if (!textures["BATTLE_TURTLE_SHEET"].loadFromFile("./Resources/Images/Sprites/Enemies/Battle turtle/BattleTurtle_animations.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BATTLE_TURTLE_TEXTURE";
    }
}

void GameState::initPausedMenu() {
    const sf::VideoMode& vm = stateData->gfxSettings->resolution;
    pmenu = new PauseMenu(stateData->gfxSettings->resolution, font, PauseTypes::PAUSE_STATE);

    pmenu->addButton("QUIT", gui::p2pY(62.5f, vm)/*450.f*/, gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initGameOverState() {
    const sf::VideoMode& vm = stateData->gfxSettings->resolution;
    gameOverMenu = new PauseMenu(stateData->gfxSettings->resolution, font, PauseTypes::GAME_OVER_STATE);

    gameOverMenu->addButton("QUIT", gui::p2pY(62.5f, vm)/*450.f*/, gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initWinState() {
    const sf::VideoMode& vm = stateData->gfxSettings->resolution;
    winMenu = new PauseMenu(stateData->gfxSettings->resolution, font, PauseTypes::WINNING_STATE);

    winMenu->addButton("QUIT", gui::p2pY(62.5f, vm)/*450.f*/, gui::p2pX(15.6f, vm), gui::p2pY(10.4f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initShaders() {
    if(!core_shader.loadFromFile("./vertex_shader.vert", "./fragment_shader.frag"))
        std::cout<<"ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
}

void GameState::initHeroes() {
    hero = new Hero(50, 50, textures["HERO_SHEET"]);
}

void GameState::initHeroGUI() {
    heroGUI = new HeroGUI(this->hero, this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap() {
    tileMap = new TileMap("./saves_file.txt");
}

void GameState::initSystems() {
    tts = new TextTagSystem("./Fonts/DeterminationMonoWebRegular-Z5oq.ttf");
}

void GameState::initDeferredRender() {
    renderTexture.create(stateData->gfxSettings->resolution.width, stateData->gfxSettings->resolution.height);
    renderSprite.setTexture(renderTexture.getTexture());
    renderSprite.setTextureRect(sf::IntRect(0, 0, stateData->gfxSettings->resolution.width, stateData->gfxSettings->resolution.height));
}

void GameState::initEnemyStrategy() {
    enemyStrategy = new EnemyFactory(this->activeEnemies, this->textures, *this->hero);
}

void GameState::initAchievements() {
    gameManager = new GameManager;
    achievements = new Achievements(*gameManager);
}


bool GameState::getKeyTime() {
    if(keyTimer.getElapsedTime().asSeconds() >= keyTimeMax){
        keyTimer.restart();
        return true;
    }
    return false;
}

void GameState::updateView(const float &dt) {
        view.setCenter(
                std::floor(hero->getPosition().x + (static_cast<float>(mousePosWindow.x) - static_cast<float>(stateData->gfxSettings->resolution.width / 2)) / 10.f),
                std::floor(hero->getPosition().y + (static_cast<float>(mousePosWindow.y) - static_cast<float>(stateData->gfxSettings->resolution.height / 2)) / 10.f)
        );

    if(tileMap->getMaxSizeF().x >= view.getSize().x) {
        if (view.getCenter().x - view.getSize().x / 2.f < 0.f) {
            view.setCenter(0.f + view.getSize().x / 2.f, view.getCenter().y);
        } else if (view.getCenter().x + view.getSize().x / 2.f > tileMap->getMaxSizeF().x) {
            view.setCenter(tileMap->getMaxSizeF().x - view.getSize().x / 2.f,
                                 view.getCenter().y);
        }
    }
    if(tileMap->getMaxSizeF().y >= view.getSize().y) {
        if (view.getCenter().y - view.getSize().y / 2.f < 0.f) {
            view.setCenter(0.f + view.getSize().x / 2.f, view.getCenter().y);
        } else if (view.getCenter().y + view.getSize().y / 2.f > tileMap->getMaxSizeF().y) {
            this->view.setCenter(view.getSize().x / 2.f,
                                 tileMap->getMaxSizeF().y - view.getCenter().y);
        }
    }
    viewGridPosition.x = static_cast<int>(view.getCenter().x) / static_cast<int>(stateData->gridSize * 2);
    viewGridPosition.y = static_cast<int>(view.getCenter().y) / static_cast<int>(stateData->gridSize);
}

void GameState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeyTime()){
        if(!paused)
            pauseState();
        else
            unpauseState();
    }
}

void GameState::updateHeroInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
        hero->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
        hero->move(1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))) {
        hero->move(0.f, -1.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN")))) {
        hero->move(0.f, 1.f, dt);
    }
}

void GameState::updateHeroGUI(const float &dt) {
    heroGUI->update(dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_HERO_TAB_CHARACTER"))) && getKeyTime()){
        heroGUI->toggleCharacterTab();
    }
}

void GameState::updatePauseMenuButtons() {
    if(pmenu->isButtonPressed("QUIT"))
        endState();

    if(gameOverMenu->isButtonPressed("QUIT"))
        endState();

    if(winMenu->isButtonPressed("QUIT"))
        endState();
}

void GameState::updateTileMap(const float &dt) {
    tileMap->updateWorldBoundsCollision(hero, dt);
    tileMap->updateTileCollision(hero, dt);
    tileMap->updateTiles(hero, dt, *enemyStrategy);
}

void GameState::updateHero(const float &dt) {
    hero->update(dt, mousePosView, this->view);

    if(hero->isDead())
        gameOver = true;
}

void GameState::updateCombatAndEnemies(const float &dt) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && hero->getWeapon()->getAttackTimer())
        hero->setInitAttack(true);

    int index = 0;
    for(auto *enemy : activeEnemies){
        enemy->update(dt, mousePosView, this->view);

        tileMap->updateWorldBoundsCollision(enemy, dt);
        tileMap->updateTileCollision(enemy, dt);

        updateCombat(enemy, index, dt);

        if(enemy->isDead()){
            gameManager->updateKills();

            if(gameManager->getKills() == 1){
                gameManager->CreateMessage("\nKILLER!\n");
                tts->addTextTag(TagTypes::ACHIEVEMENT_TAG, hero->getCenter().x, hero->getCenter().y, 1, "Achievement unlocked: +", "\nKILLER!");
            }

            if(gameManager->getKills() == 5){
                gameManager->CreateMessage("\nPENTAKILL!\n");
                tts->addTextTag(TagTypes::ACHIEVEMENT_TAG, hero->getCenter().x, hero->getCenter().y, 1, "Achievement unlocked: +", "\nPENTAKILL!");
            }

            if(gameManager->getKills() == 10){
                gameManager->CreateMessage("\nSERIAL KILLER!\n");
                tts->addTextTag(TagTypes::ACHIEVEMENT_TAG, hero->getCenter().x, hero->getCenter().y, 1, "Achievement unlocked: +", "\nSERIAL KILLER!");
            }

            hero->gainEXP(enemy->getGainExp());
            tts->addTextTag(TagTypes::EXPERIENCE_TAG, hero->getCenter().x, hero->getCenter().y, static_cast<int>(enemy->getGainExp()), "+", "EXP");

            enemyStrategy->removeEnemy(index);

            if(activeEnemies.empty())
                win = true;
            continue;
        }
        else if(enemy->getDespawnTimerDone()){
            enemyStrategy->removeEnemy(index);
            continue;
        }
        ++index;
    }
    hero->setInitAttack(false);
}

void GameState::updateCombat(Enemy* enemy, const int index, const float &dt) {
    if(hero->getInitAttack()
       && enemy->getGlobalBounds().contains(mousePosView)
       && enemy->getSpriteDistance(*hero) < hero->getWeapon()->getRange()
       && enemy->getDamageTimerDone()) {

        hero->updateAttack();

        int dmg = static_cast<int>(hero->getDamage());
        enemy->loseHP(dmg);
        enemy->resetDamageTimer();
        tts->addTextTag(TagTypes::DEFAULT_TAG, enemy->getPosition().x, enemy->getPosition().y, dmg, "", "");
    }

    if(enemy->getGlobalBounds().intersects(hero->getGlobalBounds()) && hero->getDamageTimer()){
        int dmg = enemy->getAttributeComp()->damageMax;
        hero->loseHP(dmg);
        tts->addTextTag(TagTypes::NEGATIVE_TAG, hero->getPosition().x - 30, hero->getPosition().y, dmg, "-", "HP");
    }
}

void GameState::updateDebugText(const float& dt) {
    std::stringstream  ss;

    ss << "Mouse Pos View: " << mousePosView.x << " " << mousePosView.y << "\n"
       << "Active Enemies: " << activeEnemies.size() << "\n";

    debugText.setString(ss.str());
}

void GameState::update(const float& dt) {
    updateMousePosition(&this->view);
    updateInput(dt);
    updateKeyTime(dt);

    this->updateDebugText(dt);

    if(!paused && !gameOver && !win) {
        updateView(dt);
        updateHeroInput(dt);
        updateTileMap(dt);
        updateHero(dt);
        updateHeroGUI(dt);
        updateCombatAndEnemies(dt);

        tts->update(dt);
    }
    else if (paused){
        pmenu->update(this->mousePosWindow);
        updatePauseMenuButtons();
    }
    else if (gameOver){
        gameOverMenu->update(this->mousePosWindow);
        updatePauseMenuButtons();
    }
    else if (win){
        winMenu->update(this->mousePosWindow);
        updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target) {
    if (!target)
        target = window;

    renderTexture.clear();

    renderTexture.setView(this->view);

    tileMap->render(
            renderTexture,
     viewGridPosition,
       &core_shader,
    hero->getCenter(),
   false
   );

    for(auto *enemy : activeEnemies)
        enemy->render(renderTexture, &core_shader, hero->getCenter(), false);

    hero->render(renderTexture, &core_shader, hero->getCenter(), false);

    tileMap->renderDeferred(renderTexture, &core_shader, hero->getCenter());

    tts->render(renderTexture);

    /** Render GUI **/
    renderTexture.setView(renderTexture.getDefaultView());
    heroGUI->render(renderTexture);

    /** Pause menu render **/
    if(paused)
        pmenu->render(renderTexture);

    if(gameOver)
        gameOverMenu->render(renderTexture);

    if(win)
        winMenu->render(renderTexture);

    /** Render debug text **/
    //renderTexture.draw(debugText); //debug

    /** Final render **/
    renderTexture.display();
    target->draw(renderSprite);
}
