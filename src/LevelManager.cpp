#include "LevelManager.h"
#include "TextureManager.h"
#include "Constants.h"
#include "GameException.h"
#include "Car.h"
#include "LevelLoader.h"
#include <iostream>
#include <fstream>
#include <cmath>

LevelManager::LevelManager() : m_world(nullptr), m_scoreTimeManager(nullptr) {
    m_collisionDetector = std::make_unique<CollisionDetector>();
    m_effectManager = std::make_unique<EffectManager>();
}

bool LevelManager::setLevel(std::unique_ptr<Level> level, b2World* world) {
    if (!level) {
        throw LevelOperationException("setLevel", "Cannot set null level");
    }
    if (!world) {
        throw LevelOperationException("setLevel", "Cannot set level with null physics world");
    }

    try {
        m_currentLevel = std::move(level);
        m_world = world;

        m_effectManager->setLevelManager(this);
        m_effectManager->setScoreTimeManager(m_scoreTimeManager);

        createBackground();
        spawnPlayerVehicle(world);

        return true;
    }
    catch (const std::exception& e) {
        throw LevelOperationException("setLevel", "Failed to initialize level: " + std::string(e.what()));
    }
}

void LevelManager::resetPlayerVehicle() {
    if (!m_currentLevel) {
        throw LevelOperationException("resetPlayerVehicle", "No current level available for player reset");
    }

    if (!m_world) {
        throw LevelOperationException("resetPlayerVehicle", "No physics world available for player reset");
    }

    try {
        if (m_playerVehicle) {
            m_playerVehicle->resetToStartPosition();
        }
    }
    catch (const std::exception& e) {
        throw LevelOperationException("resetPlayerVehicle", "Failed to reset player vehicle: " + std::string(e.what()));
    }
}

void LevelManager::update(float deltaTime) {
    if (!m_playerVehicle || !m_currentLevel) {
        return;
    }

    try {
        m_playerVehicle->update(deltaTime);
        updateObjects(deltaTime);
        handleCollisions();
    }
    catch (const std::exception& e) {
        throw LevelOperationException("update", "Failed to update level: " + std::string(e.what()));
    }
}

void LevelManager::handleCollisions() {
    if (!m_collisionDetector || !m_effectManager) {
        return;
    }

    std::vector<GameObject*> allObjects;
    allObjects.push_back(m_playerVehicle.get());

    if (m_currentLevel) {
        auto levelObjects = m_currentLevel->getAllObjectPointers();
        allObjects.insert(allObjects.end(), levelObjects.begin(), levelObjects.end());
    }

    auto collisionResults = m_collisionDetector->detectCollisions(allObjects);

    if (m_currentLevel) {
        auto boundaryResult = m_collisionDetector->checkPlayerBoundaryCollision(
            m_playerVehicle.get(),
            m_currentLevel->getBoundaries()
        );

        if (boundaryResult->hasCollision()) {
            collisionResults.push_back(std::move(boundaryResult));
        }
    }

    std::vector<std::unique_ptr<CollisionResult>> resultsCopy;
    for (const auto& result : collisionResults) {
        if (result) {
            resultsCopy.push_back(std::make_unique<CollisionResult>(*result));
        }
    }

    auto actions = m_effectManager->processEffectsAndGetActions(resultsCopy);

    for (const auto& action : actions) {
        switch (action.action) {
        case GameAction::RESTART_LEVEL:
            resetLevel();
            notifyGameManager(LevelEvent::LEVEL_FAILED, action.reason);
            break;
        case GameAction::NEXT_LEVEL:
            notifyGameManager(LevelEvent::LEVEL_COMPLETED, action.reason);
            break;
        case GameAction::NONE:
            break;
        }
    }
}

void LevelManager::render(sf::RenderWindow& window) {
    try {
        window.draw(m_background);

        if (!m_playerVehicle) {
            throw LevelOperationException("render", "No player vehicle available for rendering");
        }

        m_playerVehicle->draw(window);

        if (m_currentLevel) {
            renderObjects(window);
        }
    }
    catch (const std::exception& e) {
        throw LevelOperationException("render", "Failed to render level: " + std::string(e.what()));
    }
}

void LevelManager::handlePlayerInput(float deltaTime) {
    if (!m_playerVehicle) {
        throw LevelOperationException("handlePlayerInput", "No player vehicle available for input handling");
    }

    try {
        m_playerVehicle->handleInput(deltaTime);
    }
    catch (const std::exception& e) {
        throw LevelOperationException("handlePlayerInput", "Failed to handle player input: " + std::string(e.what()));
    }
}

void LevelManager::makePlayerVehicleSound() {
    if (!m_playerVehicle) {
        throw LevelOperationException("makePlayerVehicleSound", "No player vehicle available for sound");
    }

    try {
        m_playerVehicle->makeSound();
    }
    catch (const std::exception& e) {
        throw LevelOperationException("makePlayerVehicleSound", "Failed to make player vehicle sound: " + std::string(e.what()));
    }
}

void LevelManager::createBackground() {
    if (!m_currentLevel) {
        throw LevelOperationException("createBackground", "No current level for background creation");
    }

    try {
        const sf::Texture& bgTexture = TextureManager::getInstance().getTexture(m_currentLevel->getBackgroundTexture());

        m_background.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
        m_background.setTexture(&bgTexture);
    }
    catch (const std::exception& e) {
        throw LevelOperationException("createBackground", "Failed to create background: " + std::string(e.what()));
    }
}

void LevelManager::spawnPlayerVehicle(b2World* world) {
    const PlayerSpawn& spawn = m_currentLevel->getPlayerSpawn();
    m_playerVehicle = std::make_unique<Car>(spawn.position, "car_player", spawn.angle);
    m_playerVehicle->createPhysicsBody(world, spawn.position, spawn.angle);
}

void LevelManager::updateObjects(float deltaTime) {
    const auto& objects = m_currentLevel->getAllObjects();
    for (const auto& obj : objects) {
        if (!obj) {
            throw LevelOperationException("updateObjects", "Null object found in container");
        }
        obj->update(deltaTime);
    }
}

void LevelManager::renderObjects(sf::RenderWindow& window) {
    const auto& objects = m_currentLevel->getAllObjects();
    for (const auto& obj : objects) {
        if (!obj) {
            throw LevelOperationException("renderObjects", "Null object found in container");
        }
        obj->draw(window);
    }
}

void LevelManager::resetLevel() {
    if (!m_currentLevel || !m_world) {
        throw LevelOperationException("resetLevel", "Cannot reset - level or world not available");
    }

    const PlayerSpawn& spawn = m_currentLevel->getPlayerSpawn();
    m_playerVehicle = std::make_unique<Car>(spawn.position, "car_player", spawn.angle);
    m_playerVehicle->createPhysicsBody(m_world, spawn.position, spawn.angle);
}

void LevelManager::setScoreTimeManager(ScoreTimeManager* scoreTimeManager) {
    m_scoreTimeManager = scoreTimeManager;
}

void LevelManager::setEventCallback(std::function<void(LevelEvent, const std::string&)> callback) {
    m_eventCallback = callback;
}

void LevelManager::notifyGameManager(LevelEvent event, const std::string& message) {
    if (m_eventCallback) {
        m_eventCallback(event, message);
    }
}
