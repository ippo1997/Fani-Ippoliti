cmake_minimum_required(VERSION 3.16)
project(Draghi_e_Sotterranei)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(test)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Draghi_e_Sotterranei main.cpp Enemy.cpp Enemy.h GameCharacter.cpp GameCharacter.h Weapon.cpp Weapon.h Hero.cpp Hero.h TileMap.cpp TileMap.h State.cpp State.h GameState.cpp GameState.h Game.cpp Game.h MainMenuState.cpp MainMenuState.h Gui.cpp Gui.h MovementComponent.cpp MovementComponent.h AnimationComponent.cpp AnimationComponent.h EditorState.cpp EditorState.h HitboxComponent.cpp HitboxComponent.h Tile.cpp Tile.h PauseMenu.cpp PauseMenu.h SettingState.cpp SettingState.h GraphicsSettings.cpp GraphicsSettings.h precompiler.h AttributeComponent.cpp AttributeComponent.h HeroGUI.cpp HeroGUI.h Item.cpp Item.h MeleeWeapon.cpp MeleeWeapon.h Sword.cpp Sword.h SkillComponent.cpp SkillComponent.h EnemySpawnerTile.cpp EnemySpawnerTile.h EditorMode.cpp EditorMode.h DefaultEditorMode.cpp DefaultEditorMode.h EnemyEditorMode.cpp EnemyEditorMode.h EditorModes.h RegularTile.cpp RegularTile.h EnemyFactory.cpp EnemyFactory.h Items.h TextTagSystem.cpp TextTagSystem.h HeroTabs.cpp HeroTabs.h CharacterTab.cpp CharacterTab.h Tab.cpp Tab.h EnemyStrategy.cpp EnemyStrategy.h AttackStrategy.cpp AttackStrategy.h DistanceCalc.cpp DistanceCalc.h Observer.h Achievements.h Subject.h GameManager.h)
target_precompile_headers(Draghi_e_Sotterranei PUBLIC precompiler.h)
target_link_libraries(Draghi_e_Sotterranei sfml-graphics sfml-audio)
