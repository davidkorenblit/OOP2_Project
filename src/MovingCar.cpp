#include "MovingCar.h"
#include "CollisionResult.h"
#include "Constants.h"
#include "SoundManager.h"

MovingCar::MovingCar(const sf::Vector2f& startPosition, const sf::Vector2f& direction,
    float speed, float respawnDelay)
    : DynamicObstacle(startPosition, direction, speed, respawnDelay,
        sf::Vector2f(Constants::Physics::PLAYER_WIDTH, Constants::Physics::PLAYER_HEIGHT),
        "moving_car")
{
}

MovingCar::~MovingCar() {
    SoundManager::getInstance().stopSound("moving_car");
}

std::unique_ptr<CollisionResult> MovingCar::collideWith(Car* car) {
    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> MovingCar::collideWith(ParkedCar* parkedCar) {
    return CollisionResult::createNoCollision();
}

void MovingCar::update(float deltaTime) {
    if (!m_isActive) {
        if (m_respawnTimer.getElapsedTime().asSeconds() >= m_respawnDelay) {
            respawn();
        }
        return;
    }

    sf::Vector2f currentPos = getPosition();
    sf::Vector2f newPos = currentPos + m_direction * m_speed * deltaTime;
    setPosition(newPos);

    if (isOffScreen()) {
        SoundManager::getInstance().stopSound("moving_car");
        SoundManager::getInstance().setSoundVolume("drive", 80.0f);

        m_isActive = false;
        m_respawnTimer.restart();
    }
}

void MovingCar::respawn() {
    setPosition(m_startPosition);
    m_isActive = true;
    SoundManager::getInstance().setSoundVolume("drive", 40.0f);
    SoundManager::getInstance().playSound("moving_car");
}