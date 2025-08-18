#pragma once
#include "LevelManager.h"
#include "CollisionDetector.h"
#include "EffectManager.h"
#include "MenuManager.h"
#include "ScoreTimeManager.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>

class Vehicle;

enum class GameState {
    LOADING,
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    YOU_WIN
};

class GameManager {
public:
    GameManager();
    ~GameManager();

    void initialize();
    void run();
    void shutdown();

    void startGame();
    void goToNextLevel();
    void restartGame();
    void restartCurrentLevel();
    int getCurrentLevelNumber() const { return m_currentLevelNumber; }
    bool hasNextLevel() const;

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Font m_font;
    sf::Text m_uiText;

    std::unique_ptr<b2World> m_world;
    std::unique_ptr<LevelManager> m_levelManager;
    std::unique_ptr<MenuManager> m_menuManager;
    std::unique_ptr<ScoreTimeManager> m_scoreTimeManager;

    bool m_isRunning;
    bool m_fontLoaded;
    GameState m_gameState;
    int m_currentLevelNumber;
    bool m_gameWon;

    void renderFullScreenTexture(const std::string& textureId);
    void playScreenSoundOnce(const std::string& soundId, bool& soundPlayed);

    void processEvents();
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render();
    void initializeMenu();

    void initializePhysics();
    void initializeManagers();
    void loadLevel(int levelNumber);
    void initializeUI();
    void setupUIText();

    void handleWindowEvents(const sf::Event& event);
    void handleMenuEvents(const sf::Event& event);
    void handleGameplayEvents(const sf::Event& event);
    void handleEscapeKey();
    void updatePhysics(float deltaTime);
    void renderYouWinScreen();

    void updateUI();
    void updateGameState();
    void renderMenuScreen();
    std::string buildUIString(Vehicle* playerVehicle);
    void renderGameplay();
    void renderPauseOverlay();
    void renderGameOverScreen();

    void togglePause();
    void handleLevelEvent(LevelEvent event, const std::string& message);

    void processCollisionResults(std::vector<std::unique_ptr<CollisionResult>>& results);
    void checkGameWonCondition();
    void resetGameState();

    bool levelFileExists(int levelNumber) const;
    float calculateTimeForLevel(int levelNumber) const;
};