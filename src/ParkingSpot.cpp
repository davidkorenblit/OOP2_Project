#include "ParkingSpot.h"
#include "TextureManager.h"
#include "Constants.h"
#include "CollisionResult.h"
#include "Motorcycle.h"
#include <iostream>

ParkingSpot::ParkingSpot(const sf::Vector2f& position, const std::string& textureId)
    : GameObject(sf::Vector2f(180.0f, 100.0f), textureId)
    , m_spotWidth(180.0f)
    , m_spotHeight(100.0f)
    , m_isOccupied(false)
{
    setPosition(position);
}

std::unique_ptr<CollisionResult> ParkingSpot::acceptCollision(GameObject* other) {
    return other->collideWith(this);
}

bool ParkingSpot::isFullyContained(const sf::FloatRect& vehicleBounds) const {
    sf::FloatRect spotBounds = getBounds();
    const float TOLERANCE = 10.0f;

    bool leftInside = vehicleBounds.left >= (spotBounds.left - TOLERANCE);
    bool rightInside = (vehicleBounds.left + vehicleBounds.width) <= (spotBounds.left + spotBounds.width + TOLERANCE);
    bool topInside = vehicleBounds.top >= (spotBounds.top - TOLERANCE);
    bool bottomInside = (vehicleBounds.top + vehicleBounds.height) <= (spotBounds.top + spotBounds.height + TOLERANCE);

    return leftInside && rightInside && topInside && bottomInside;
}

std::unique_ptr<CollisionResult> ParkingSpot::collideWith(Car* car) {
    if (!car) {
        return CollisionResult::createNoCollision();
    }

    sf::FloatRect vehicleBounds = car->getBounds();

    if (isFullyContained(vehicleBounds)) {
        std::cout << "PARKING SUCCESS!" << std::endl;
        return std::make_unique<CollisionResult>(
            CollisionType::GOAL_REACHED,
            500,
            0,
            true,
            EffectType::COLLECT_SOUND,
            "Perfect parking! Next Level!"
        );
    }

    return CollisionResult::createNoCollision();
}





std::unique_ptr<CollisionResult> ParkingSpot::collideWith(Vehicle* vehicle) {
    if (!vehicle) {
        return CollisionResult::createNoCollision();
    }

    sf::FloatRect vehicleBounds = vehicle->getBounds();

    if (isFullyContained(vehicleBounds)) {
        std::cout << "VEHICLE PARKING SUCCESS!" << std::endl;
        return std::make_unique<CollisionResult>(
            CollisionType::GOAL_REACHED,
            400,
            0,
            true,
            EffectType::COLLECT_SOUND,
            "Vehicle parked! Next Level!"
        );
    }

    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> ParkingSpot::collideWith(StaticObstacle* obstacle) {
    return CollisionResult::createNoCollision();
}

std::unique_ptr<CollisionResult> ParkingSpot::collideWith(DynamicObstacle* obstacle) {
    return CollisionResult::createNoCollision();
}



std::unique_ptr<CollisionResult> ParkingSpot::collideWith(ParkingSpot* parkingSpot) {
    return CollisionResult::createNoCollision();
}

//std::unique_ptr<CollisionResult> ParkingSpot::collideWith(RoadBoundary* roadBoundary) {
//    return CollisionResult::createNoCollision();
//}

std::unique_ptr<CollisionResult> ParkingSpot::collideWith(ParkedCar* parkedCar) {
    return CollisionResult::createNoCollision();
}

void ParkingSpot::update(float deltaTime) {
}

//sf::Vector2f ParkingSpot::getPosition() const {
//    return m_fixedPosition;
//}
//
//void ParkingSpot::setPosition(const sf::Vector2f& position) {
//    m_fixedPosition = position;
//}