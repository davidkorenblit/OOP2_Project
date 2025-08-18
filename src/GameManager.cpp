#include "GameManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Constants.h"
#include "GameException.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "LevelLoader.h"

GameManager::GameManager()
    : m_window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), Constants::WINDOW_TITLE)
    , m_isRunning(false)
    , m_fontLoaded(false)
    , m_gameState(GameState::MENU)
    , m_currentLevelNumber(1)
    , m_gameWon(false)
{
    m_window.setFramerateLimit(Constants::FPS);
}

GameManager::~GameManager() {
    shutdown();
}

void GameManager::renderFullScreenTexture(const std::string& textureId) {
    TextureManager& tm = TextureManager::getInstance();
    const sf::Texture& texture = tm.getTexture(textureId);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();
    sf::Vector2f windowSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);

    sprite.setScale(
        windowSize.x / textureSize.x,
        windowSize.y / textureSize.y
    );

    m_window.draw(sprite);
}

void GameManager::playScreenSoundOnce(const std::string& soundId, bool& soundPlayed) {
    if (!soundPlayed) {
        SoundManager::getInstance().stopAllSounds();
        SoundManager::getInstance().playSound(soundId);
        soundPlayed = true;
    }
}

void GameManager::initialize() {
    try {
        TextureManager::getInstance().loadAllGameTextures();

        SoundManager::getInstance().loadAllGameSounds();
        SoundManager::getInstance().playBackgroundLoop("game_start");

        initializeUI();
        m_scoreTimeManager = std::make_unique<ScoreTimeManager>();
        initializeMenu();
        m_isRunning = true;
        m_gameState = GameState::MENU;
    }
    catch (const GameException& e) {
        std::cerr << "Game initialization failed: " << e.getFullMessage() << std::endl;
        throw;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error during initialization: " << e.what() << std::endl;
        throw ManagerInitializationException("GameManager", "Unexpected initialization error");
    }
}

void GameManager::startGame() {
    loadLevel(m_currentLevelNumber);
    m_scoreTimeManager->startLevel(m_currentLevelNumber, calculateTimeForLevel(m_currentLevelNumber));
    m_gameState = GameState::PLAYING;
}

void GameManager::goToNextLevel() {
    if (hasNextLevel()) {
        m_currentLevelNumber++;
        loadLevel(m_currentLevelNumber);
        m_scoreTimeManager->startLevel(m_currentLevelNumber, calculateTimeForLevel(m_currentLevelNumber));
    }
    else {
        m_gameState = GameState::YOU_WIN;
    }
}

void GameManager::restartGame() {
    resetGameState();
    m_gameState = GameState::LOADING;
    loadLevel(m_currentLevelNumber);
    m_scoreTimeManager->startLevel(m_currentLevelNumber, calculateTimeForLevel(m_currentLevelNumber));
    m_gameState = GameState::PLAYING;
}

void GameManager::restartCurrentLevel() {
    loadLevel(m_currentLevelNumber);
    m_scoreTimeManager->startLevel(m_currentLevelNumber, calculateTimeForLevel(m_currentLevelNumber));
}

bool GameManager::hasNextLevel() const {
    return levelFileExists(m_currentLevelNumber + 1);
}

bool GameManager::levelFileExists(int levelNumber) const {
    std::string filename = "level" + std::to_string(levelNumber) + ".json";
    std::ifstream file(filename);
    return file.good();
}

float GameManager::calculateTimeForLevel(int levelNumber) const {
    return 60.0f * std::pow(1.5f, levelNumber - 1);
}

void GameManager::loadLevel(int levelNumber) {
    std::string levelFile = "level" + std::to_string(levelNumber) + ".json";
    auto level = LevelLoader::loadFromFile(levelFile, levelNumber);
    if (!level) {
        throw InvalidLevelException(levelFile, "Failed to load level from file");
    }
    if (!m_levelManager->setLevel(std::move(level), m_world.get())) {
        throw LevelOperationException("setLevel", "Failed to set level in LevelManager");
    }
}

void GameManager::initializeMenu() {
    if (m_fontLoaded) {
        m_menuManager = std::make_unique<MenuManager>(&m_font);
        m_menuManager->initializeMenu();
    }
}

void GameManager::run() {
    while (m_isRunning && m_window.isOpen()) {
        sf::Time deltaTime = m_clock.restart();
        float dt = deltaTime.asSeconds();

        try {
            processEvents();

            if (m_gameState == GameState::PLAYING) {
                handleInput(dt);
                update(dt);
            }

            if (m_gameState == GameState::MENU && m_menuManager) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                m_menuManager->update(sf::Vector2f(mousePos.x, mousePos.y));
            }

            render();
        }
        catch (const GameStateException& e) {
            if (e.getStateName() == "GameWon") {
                m_gameState = GameState::YOU_WIN;
            }
            else if (e.getStateName() == "GameRestart") {
                restartGame();
            }
            else {
                std::cerr << "Game state error: " << e.getFullMessage() << std::endl;
            }
        }
        catch (const GameException& e) {
            std::cerr << "Game error: " << e.getFullMessage() << std::endl;
            m_gameState = GameState::GAME_OVER;
        }
        catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << std::endl;
            m_gameState = GameState::GAME_OVER;
        }
    }
}

void GameManager::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        handleWindowEvents(event);

        if (m_gameState == GameState::PLAYING || m_gameState == GameState::YOU_WIN) {
            handleGameplayEvents(event);
        }

        if (m_gameState == GameState::MENU) {
            handleMenuEvents(event);
        }
    }
}

void GameManager::handleInput(float deltaTime) {
    if (!m_levelManager) {
        throw ManagerInitializationException("LevelManager", "LevelManager not available for input handling");
    }

    if (m_gameState == GameState::PLAYING) {
        m_levelManager->handlePlayerInput(deltaTime);
    }
}

void GameManager::update(float deltaTime) {
    if (m_gameState != GameState::PLAYING) return;

    SoundManager::getInstance().update();
    m_scoreTimeManager->update();

    if (m_scoreTimeManager->isTimeUp()) {
        m_gameState = GameState::GAME_OVER;
        return;
    }

    updatePhysics(deltaTime);

    if (m_levelManager) {
        m_levelManager->update(deltaTime);
    }

    checkGameWonCondition();
    updateUI();
    updateGameState();
}

void GameManager::processCollisionResults(std::vector<std::unique_ptr<CollisionResult>>& results) {
    for (auto& result : results) {
        if (result && result->getType() == CollisionType::GOAL_REACHED) {
            m_gameWon = true;
        }
    }
}

void GameManager::checkGameWonCondition() {
    if (m_gameWon) {
        m_gameState = GameState::YOU_WIN;
        m_gameWon = false;
    }
}

void GameManager::resetGameState() {
    m_gameWon = false;
}

void GameManager::render() {
    m_window.clear(sf::Color(40, 40, 40));

    switch (m_gameState) {
    case GameState::MENU:
        renderMenuScreen();
        break;
    case GameState::LOADING:
        break;
    case GameState::PLAYING:
        renderGameplay();
        break;
    case GameState::PAUSED:
        renderGameplay();
        renderPauseOverlay();
        break;
    case GameState::GAME_OVER:
        renderGameplay();
        renderGameOverScreen();
        break;
    case GameState::YOU_WIN:
        renderGameplay();
        renderYouWinScreen();
        break;
    }

    m_window.display();
}

void GameManager::shutdown() {
    SoundManager::shutdown();
    m_scoreTimeManager.reset();
    m_levelManager.reset();
    m_world.reset();
    m_menuManager.reset();

    TextureManager::shutdown();
}

void GameManager::initializePhysics() {
    m_world = std::make_unique<b2World>(b2Vec2(0.0f, 0.0f));
    if (!m_world) {
        throw ManagerInitializationException("PhysicsWorld", "Failed to create Box2D world");
    }
}

void GameManager::initializeManagers() {
    try {
        m_levelManager = std::make_unique<LevelManager>();

        m_levelManager->setScoreTimeManager(m_scoreTimeManager.get());

        m_levelManager->setEventCallback([this](LevelEvent event, const std::string& message) {
            handleLevelEvent(event, message);
            });

    }
    catch (const std::exception& e) {
        std::cerr << "Exception in initializeManagers: " << e.what() << std::endl;
        throw;
    }
}

void GameManager::handleLevelEvent(LevelEvent event, const std::string& message) {
    switch (event) {
    case LevelEvent::LEVEL_COMPLETED:
        goToNextLevel();
        break;
    case LevelEvent::LEVEL_FAILED:
        restartCurrentLevel();
        break;
    case LevelEvent::PLAYER_DIED:
        m_gameState = GameState::GAME_OVER;
        break;
    }
}

void GameManager::initializeUI() {
    m_fontLoaded = m_font.loadFromFile(Constants::Assets::RETRO_FONT);
    if (m_fontLoaded) {
        setupUIText();
    }
}

void GameManager::setupUIText() {
    m_uiText.setFont(m_font);
    m_uiText.setCharacterSize(16);
    m_uiText.setFillColor(Constants::Colors::WHITE);
    m_uiText.setPosition(10, 10);
}

void GameManager::handleWindowEvents(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        m_isRunning = false;
        m_window.close();
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            handleEscapeKey();
        }
    }
}

void GameManager::handleMenuEvents(const sf::Event& event) {
    if (!m_menuManager) return;

    MenuOption option = m_menuManager->handleMenuInput(event);

    switch (option) {
    case MenuOption::START_GAME:
    {
        SoundManager::getInstance().stopAllBackgroundSounds();
        initializePhysics();
        initializeManagers();
        startGame();
        break;
    }
    case MenuOption::EXIT:
        m_isRunning = false;
        m_window.close();
        break;
    case MenuOption::INSTRUCTIONS:
        break;
    default:
        break;
    }
}

void GameManager::handleGameplayEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::H:
            if (!m_levelManager) {
                throw ManagerInitializationException("LevelManager", "LevelManager not available for sound");
            }
            m_levelManager->makePlayerVehicleSound();
            break;
        case sf::Keyboard::P:
            if (m_gameState == GameState::PLAYING) {
                togglePause();
            }
            break;
        case sf::Keyboard::R:
            restartGame();
            break;
        case sf::Keyboard::M:
            if (m_gameState == GameState::GAME_OVER) {
                m_gameState = GameState::MENU;
                SoundManager::getInstance().stopAllSounds();
                SoundManager::getInstance().playBackgroundLoop("game_start");
            }
            break;
        default:
            break;
        }
    }
}

void GameManager::handleEscapeKey() {
    switch (m_gameState) {
    case GameState::PLAYING:
        m_gameState = GameState::PAUSED;
        break;
    case GameState::PAUSED:
        m_gameState = GameState::PLAYING;
        break;
    default:
        m_isRunning = false;
        m_window.close();
        break;
    }
}

void GameManager::updatePhysics(float deltaTime) {
    if (!m_world) {
        throw ManagerInitializationException("PhysicsWorld", "Physics world not available for update");
    }

    float timeStep = deltaTime;
    if (timeStep > 1.0f / 30.0f) {
        timeStep = 1.0f / 30.0f;
    }

    const int velocityIterations = 6;
    const int positionIterations = 2;

    m_world->Step(timeStep, velocityIterations, positionIterations);
}

void GameManager::updateUI() {
    if (!m_fontLoaded || !m_levelManager || !m_levelManager->getPlayerVehicle()) {
        return;
    }

    auto playerVehicle = m_levelManager->getPlayerVehicle();
    std::string uiInfo = buildUIString(playerVehicle);
    m_uiText.setString(uiInfo);
}

std::string GameManager::buildUIString(Vehicle* playerVehicle) {
    return m_scoreTimeManager->getUIString();
}

void GameManager::updateGameState() {
}

void GameManager::renderMenuScreen() {
    m_window.clear(sf::Color(30, 30, 30));

    if (m_menuManager) {
        m_menuManager->renderMenu(m_window);
    }
}

void GameManager::renderGameplay() {
    if (!m_levelManager) {
        throw ManagerInitializationException("LevelManager", "LevelManager not available for rendering");
    }

    m_levelManager->render(m_window);

    if (m_fontLoaded) {
        m_window.draw(m_uiText);
    }
}

void GameManager::renderPauseOverlay() {
    sf::RectangleShape overlay(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));
    m_window.draw(overlay);

    if (m_fontLoaded) {
        sf::Text pauseText("PAUSED - Press ESC to continue", m_font, 24);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setPosition(Constants::WINDOW_WIDTH / 2 - 200, Constants::WINDOW_HEIGHT / 2);
        m_window.draw(pauseText);
    }
}

void GameManager::renderGameOverScreen() {
    renderFullScreenTexture("gameover");

    static bool gameOverSoundPlayed = false;
    playScreenSoundOnce("gameover", gameOverSoundPlayed);
}

void GameManager::renderYouWinScreen() {
    renderFullScreenTexture("youwin");

    if (!SoundManager::getInstance().isCurrentlyPlaying("victory")) {
        SoundManager::getInstance().stopAllSounds();
        SoundManager::getInstance().playSound("victory");
    }
}

void GameManager::togglePause() {
    if (m_gameState == GameState::PLAYING) {
        m_gameState = GameState::PAUSED;
    }
    else if (m_gameState == GameState::PAUSED) {
        m_gameState = GameState::PLAYING;
    }
}