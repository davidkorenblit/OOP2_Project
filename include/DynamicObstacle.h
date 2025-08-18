#pragma once
#include "GameObject.h"
#include <SFML/System/Clock.hpp>

class DynamicObstacle : public GameObject {
protected:
    sf::Vector2f m_startPosition;
    sf::Vector2f m_direction;
    float m_speed;
    float m_respawnDelay;
    sf::Clock m_respawnTimer;
    bool m_isActive;

public:
    DynamicObstacle(const sf::Vector2f& startPosition, const sf::Vector2f& direction,
        float speed, float respawnDelay, const sf::Vector2f& size,
        const std::string& textureId);
    virtual ~DynamicObstacle() = default;

    std::unique_ptr<CollisionResult> acceptCollision(GameObject* other) override;
    virtual std::unique_ptr<CollisionResult> collideWith(Car* car) = 0;
    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override;
    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override;
    //std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override;
    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override;
    void update(float deltaTime) override;
    //sf::FloatRect getBounds() const override;

    bool isVehicle() const override { return true; }
    bool isParkingSpot() const override { return false; }
    bool isPlayerVehicle() const override { return false; }

    bool isActive() const { return m_isActive; }
    void respawn();
    bool isOffScreen() const;
};