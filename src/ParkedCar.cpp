#include "ParkedCar.h"
#include "Constants.h"
#include "CollisionResult.h"
#include "Car.h"
#include "Motorcycle.h"
#include <iostream>

ParkedCar::ParkedCar(const sf::Vector2f& position, const std::string& textureId)
    : StaticObstacle(position, textureId)
    , m_carWidth(50.0f)
    , m_carHeight(100.0f)
{
}

std::unique_ptr<CollisionResult> ParkedCar::acceptCollision(GameObject* other) {
    return other->collideWith(this);
}

std::unique_ptr<CollisionResult> ParkedCar::collideWith(Car* car) {
    return std::make_unique<CollisionResult>(
        CollisionType::HEAVY_DAMAGE,
        -200,
        75,
        true,
        EffectType::CRASH,
        "Player car crashed into parked car!"
    );
}


std::unique_ptr<CollisionResult> ParkedCar::collideWith(Vehicle* vehicle) {
    return std::make_unique<CollisionResult>(
        CollisionType::HEAVY_DAMAGE,
        -150,
        60,
        true,
        EffectType::CRASH,
        "Vehicle crashed into parked car!"
    );
}

std::unique_ptr<CollisionResult> ParkedCar::collideWith(ParkedCar* parkedCar) {
    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> ParkedCar::collideWith(StaticObstacle* obstacle) {
    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> ParkedCar::collideWith(DynamicObstacle* obstacle) {
    return CollisionResult::createNoCollision();
}



std::unique_ptr<CollisionResult> ParkedCar::collideWith(ParkingSpot* parkingSpot) {
    return CollisionResult::createNoCollision();
}

//std::unique_ptr<CollisionResult> ParkedCar::collideWith(RoadBoundary* roadBoundary) {
//    return CollisionResult::createNoCollision();
//}

void ParkedCar::update(float deltaTime) {
    sf::Vector2f currentPos = getPosition();
    m_sprite.setPosition(currentPos);
}


