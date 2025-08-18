#pragma once
#include "GameObject.h"

class StaticObstacle : public GameObject {
private:
    std::string m_obstacleType;
    sf::Vector2f m_fixedPosition;

public:
    StaticObstacle(const sf::Vector2f& position, const std::string& textureId = "traffic_cone");
    virtual ~StaticObstacle() = default;

    std::unique_ptr<CollisionResult> acceptCollision(GameObject* other) override;
    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override;
    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override;
    //std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override;
    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override;

    void update(float deltaTime) override;
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f& position) override;
    //sf::FloatRect getBounds() const override;

    bool isVehicle() const override { return false; }
    bool isParkingSpot() const override { return false; }
    bool isPlayerVehicle() const override { return false; }

    bool canBeMoved() const { return true; }
};