#pragma once
#include "StaticObstacle.h"

class Car;
class ParkedCar : public StaticObstacle {
private:
    float m_carWidth;
    float m_carHeight;

public:
    ParkedCar(const sf::Vector2f& position, const std::string& textureId);
    ~ParkedCar() {
        printf("ParkedCar destroyed - ID:%d\n", getId());
    }

    std::unique_ptr<CollisionResult> acceptCollision(GameObject* other) override;
    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override;
    //std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override;
    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override;
    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override;

    bool isVehicle() const override { return true; }
    bool isParkingSpot() const override { return false; }
    bool isPlayerVehicle() const override { return false; }

    void update(float deltaTime) override;
    //sf::FloatRect getBounds() const override;
};