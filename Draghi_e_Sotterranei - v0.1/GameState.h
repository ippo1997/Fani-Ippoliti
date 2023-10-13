//
// Created by alpacox on 26/03/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_GAMESTATE_H
#define DRAGHI_E_SOTTERRANEI_GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "HeroGUI.h"
#include "Sword.h"
#include "TextTagSystem.h"
#include "Observer.h"
#include "Achievements.h"
#include "GameManager.h"

using namespace std;

class GameState: public State {
public:
    explicit GameState(StateData* state_data);
    ~GameState() override;

    bool getKeyTime() override;

    void updateView(const float& dt);
    void updateInput(const float& dt) override;
    void updateHeroInput(const float& dt);
    void updateHeroGUI(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void updateHero(const float& dt);
    void updateCombatAndEnemies(const float& dt);
    void updateCombat(Enemy* enemy,  int index, const float& dt);
    void updateDebugText(const float& dt);
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;

private:
    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu* pmenu;
    PauseMenu* gameOverMenu;
    PauseMenu* winMenu;

    sf::Shader core_shader;

    sf::Clock keyTimer;
    float keyTimeMax;

    sf::Text debugText;

    Hero* hero;
    HeroGUI* heroGUI;
    sf::Texture texture;

    TileMap* tileMap;

    TextTagSystem *tts;

    std::vector<Enemy*> activeEnemies;
    EnemyFactory *enemyStrategy;

    void initView();
    void initKeybinds() override;
    void initFonts();
    void initTextures();
    void initPausedMenu();
    void initGameOverState();
    void initWinState();
    void initShaders();
    void initHeroes();
    void initHeroGUI();
    void initTileMap();
    void initSystems();
    void initDeferredRender();
    void initEnemyStrategy();
    void initKeyTime();
    void initDebugText();

    void initAchievements();

    GameManager* gameManager;
    Achievements* achievements;

};

#endif //DRAGHI_E_SOTTERRANEI_GAMESTATE_H
