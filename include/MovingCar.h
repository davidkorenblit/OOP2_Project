#pragma once
#include "DynamicObstacle.h"

class MovingCar : public DynamicObstacle {
public:
    MovingCar(const sf::Vector2f& startPosition, const sf::Vector2f& direction,
        float speed, float respawnDelay);
    virtual ~MovingCar();

    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override;
    void update(float deltaTime) override;
    void respawn();
};