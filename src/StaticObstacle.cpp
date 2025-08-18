#include "StaticObstacle.h"
#include "Constants.h"
#include "CollisionResult.h"
#include <iostream>

StaticObstacle::StaticObstacle(const sf::Vector2f& position, const std::string& textureId)
    : GameObject(sf::Vector2f(30.0f, 30.0f), textureId)
    , m_obstacleType("TrafficCone")
    , m_fixedPosition(position)
{
    setPosition(position);
   // std::cout << "StaticObstacle created - Type: " << m_obstacleType << std::endl;
}

std::unique_ptr<CollisionResult> StaticObstacle::acceptCollision(GameObject* other) {
    return other->collideWith(this);
}

std::unique_ptr<CollisionResult> StaticObstacle::collideWith(Car* car) {
    return std::make_unique<CollisionResult>(
        CollisionType::MINOR_DAMAGE,
        -10,
        10,
        false,
        EffectType::SPARKS,
        "Car hit traffic cone"
    );
}


std::unique_ptr<CollisionResult> StaticObstacle::collideWith(Vehicle* vehicle) {
    return std::make_unique<CollisionResult>(
        CollisionType::MINOR_DAMAGE,
        -8,
        8,
        false,
        EffectType::SPARKS,
        "Vehicle hit static obstacle"
    );
}

std::unique_ptr<CollisionResult> StaticObstacle::collideWith(StaticObstacle* obstacle) {
    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> StaticObstacle::collideWith(DynamicObstacle* obstacle) {
    return CollisionResult::createNoCollision();
}



std::unique_ptr<CollisionResult> StaticObstacle::collideWith(ParkingSpot* parkingSpot) {
    return CollisionResult::createNoCollision();
}

//std::unique_ptr<CollisionResult> StaticObstacle::collideWith(RoadBoundary* roadBoundary) {
//    return CollisionResult::createNoCollision();
//}

std::unique_ptr<CollisionResult> StaticObstacle::collideWith(ParkedCar* parkedCar) {
    return CollisionResult::createNoCollision();
}

void StaticObstacle::update(float deltaTime) {
}

sf::Vector2f StaticObstacle::getPosition() const {
    return m_fixedPosition;
}

void StaticObstacle::setPosition(const sf::Vector2f& position) {
    m_fixedPosition = position;
    m_sprite.setPosition(position);

   // sf::Transformable::setPosition(position);
}