//#pragma once
//#include "Vehicle.h"
//
//class Truck : public Vehicle {
//private:
//    int m_health;
//
//public:
//    Truck(const sf::Vector2f& position, const std::string& textureId = "truck");
//    virtual ~Truck() = default;
//
//    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
//    std::unique_ptr<CollisionResult> collideWith(Motorcycle* motorcycle) override;
//    std::unique_ptr<CollisionResult> collideWith(Truck* truck) override;
//    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override;
//    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override;
//    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override;
//    std::unique_ptr<CollisionResult> collideWith(PowerUp* powerup) override;
//    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override;
//    std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override;
//
//    void update(float deltaTime) override;
//    void handleInput(float deltaTime) override;
//    void makeSound() override;
//    int getHealth() const override;
//    void takeDamage(int damage) override;
//    bool isDestroyed() const override;
//    void repair() override;
//    void resetToStartPosition() override;
//    void applySpeedBoost(float multiplier, float duration) override;
//    void removeSpeedBoost() override;
//    void applyShield(int protectionLevel) override;
//    void removeShield() override;
//    bool hasShield() const override;
//    void applyTimeBonus(int bonusTime) override;
//};