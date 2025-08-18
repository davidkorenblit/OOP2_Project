#include "DynamicObstacle.h"
#include "CollisionResult.h"
#include "Constants.h"

DynamicObstacle::DynamicObstacle(const sf::Vector2f& startPosition, const sf::Vector2f& direction,
    float speed, float respawnDelay, const sf::Vector2f& size,
    const std::string& textureId)
    : GameObject(size, textureId)
    , m_startPosition(startPosition)
    , m_direction(direction)
    , m_speed(speed)
    , m_respawnDelay(respawnDelay)
    , m_isActive(true)
{
    setPosition(startPosition);
}

std::unique_ptr<CollisionResult> DynamicObstacle::acceptCollision(GameObject* other) {
    return other->collideWith(this);
}



std::unique_ptr<CollisionResult> DynamicObstacle::collideWith(Vehicle* vehicle) {
    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> DynamicObstacle::collideWith(StaticObstacle* obstacle) {
    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> DynamicObstacle::collideWith(DynamicObstacle* obstacle) {
    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> DynamicObstacle::collideWith(ParkingSpot* parkingSpot) {
    return CollisionResult::createNoCollision();
}

//std::unique_ptr<CollisionResult> DynamicObstacle::collideWith(RoadBoundary* roadBoundary) {
//    return CollisionResult::createNoCollision();
//}

std::unique_ptr<CollisionResult> DynamicObstacle::collideWith(ParkedCar* parkedCar)
{
    return CollisionResult::createNoCollision();
}

void DynamicObstacle::update(float deltaTime) {
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
        m_isActive = false;
        m_respawnTimer.restart();
    }
}

//sf::Vector2f DynamicObstacle::getPosition() const {
//    return sf::Transformable::getPosition();
//}
//
//void DynamicObstacle::setPosition(const sf::Vector2f& position) {
//    sf::Transformable::setPosition(position);
//}

void DynamicObstacle::respawn() {
    setPosition(m_startPosition);
    m_isActive = true;
}

bool DynamicObstacle::isOffScreen() const {
    sf::Vector2f pos = getPosition();
    return pos.x < -100 || pos.x > Constants::WINDOW_WIDTH + 100 ||
        pos.y < -100 || pos.y > Constants::WINDOW_HEIGHT + 100;
}