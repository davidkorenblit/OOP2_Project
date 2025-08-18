#pragma once
#include "Level.h"
#include "Vehicle.h"
#include "ScoreTimeManager.h"
#include "CollisionDetector.h"
#include "EffectManager.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include <vector>
#include <functional>

enum class LevelEvent {
    LEVEL_COMPLETED,
    LEVEL_FAILED,
    PLAYER_DIED
};

class LevelManager {
private:
    std::unique_ptr<Level> m_currentLevel;
    std::unique_ptr<Vehicle> m_playerVehicle;
    std::unique_ptr<CollisionDetector> m_collisionDetector;
    std::unique_ptr<EffectManager> m_effectManager;
    sf::RectangleShape m_background;
    b2World* m_world;
    ScoreTimeManager* m_scoreTimeManager;

    std::function<void(LevelEvent, const std::string&)> m_eventCallback;

    void createBackground();
    void spawnPlayerVehicle(b2World* world);
    void updateObjects(float deltaTime);
    void renderObjects(sf::RenderWindow& window);
    void handleCollisions();
    void notifyGameManager(LevelEvent event, const std::string& message = "");

public:
    LevelManager();
    ~LevelManager() = default;

    void setEventCallback(std::function<void(LevelEvent, const std::string&)> callback);
    void setScoreTimeManager(ScoreTimeManager* scoreTimeManager);
    bool setLevel(std::unique_ptr<Level> level, b2World* world);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void handlePlayerInput(float deltaTime);
    void makePlayerVehicleSound();
    void resetPlayerVehicle();
    void resetLevel();
    Level* getCurrentLevel() const { return m_currentLevel.get(); }
    Vehicle* getPlayerVehicle() const { return m_playerVehicle.get(); }
};