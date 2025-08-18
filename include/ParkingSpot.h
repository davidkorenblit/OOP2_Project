#pragma once
#include "GameObject.h"
#include "Car.h"

class ParkingSpot : public GameObject {
private:
    float m_spotWidth;
    float m_spotHeight;
    bool m_isOccupied;

public:
    ParkingSpot(const sf::Vector2f& position, const std::string& textureId = "parking_spot");
    virtual ~ParkingSpot() = default;

    std::unique_ptr<CollisionResult> acceptCollision(GameObject* other) override;
    bool isFullyContained(const sf::FloatRect& carBounds) const;
    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override;
    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override;
    //std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override;
    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override;

    void update(float deltaTime) override;

    bool isVehicle() const override { return false; }
    bool isParkingSpot() const override { return true; }
    bool isPlayerVehicle() const override { return false; }

    bool isOccupied() const { return m_isOccupied; }
    void setOccupied(bool occupied) { m_isOccupied = occupied; }
};