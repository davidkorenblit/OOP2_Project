//#pragma once
//#include "DynamicObstacle.h"
//
//class MovingPedestrian : public DynamicObstacle {
//public:
//    MovingPedestrian(const sf::Vector2f& startPosition, const sf::Vector2f& direction,
//        float speed, float respawnDelay);
//    virtual ~MovingPedestrian() = default;
//
//    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
//    std::unique_ptr<CollisionResult> collideWith(Motorcycle* motorcycle) override;
//    std::unique_ptr<CollisionResult> collideWith(Truck* truck) override;
//
//};