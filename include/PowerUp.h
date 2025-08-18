//#pragma once
//#include "GameObject.h"
//#include <SFML/System/Clock.hpp>
//
//class Vehicle;
//
//class PowerUp : public GameObject {
//protected:
//    bool m_isCollected;
//    int m_scoreValue;
//    sf::Clock m_activationTimer;
//    float m_duration;
//    bool m_isActive;
//
//public:
//    PowerUp(const sf::Vector2f& position, const sf::Vector2f& size,
//        const std::string& texturePath, int scoreValue = 100);
//    virtual ~PowerUp() = default;
//
//    std::unique_ptr<CollisionResult> acceptCollision(GameObject* other) override;
//    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
//    std::unique_ptr<CollisionResult> collideWith(Motorcycle* motorcycle) override;
//    std::unique_ptr<CollisionResult> collideWith(Truck* truck) override;
//    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override;
//    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override;
//    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override;
//    std::unique_ptr<CollisionResult> collideWith(PowerUp* powerUp) override;
//    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override;
//    std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override;
//
//    void update(float deltaTime) override;
//    sf::Vector2f getPosition() const override;
//    void setPosition(const sf::Vector2f& position) override;
//    sf::FloatRect getBounds() const override;
//
//    bool isVehicle() const override { return false; }
//    bool isParkingSpot() const override { return false; }
//    bool isPlayerVehicle() const override { return false; }
//
//    virtual void activate(Vehicle* vehicle) = 0;
//    virtual void deactivate(Vehicle* vehicle) = 0;
//
//    void collect();
//    bool isCollected() const { return m_isCollected; }
//    bool isActive() const { return m_isActive; }
//    bool isExpired() const;
//    int getScoreValue() const { return m_scoreValue; }
//};