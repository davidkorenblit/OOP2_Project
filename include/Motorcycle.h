//#pragma once
//#include "Vehicle.h"
//#include <SFML/Audio.hpp>
//
//class Car;
//class Truck;
//class StaticObstacle;
//class DynamicObstacle;
//class PowerUp;
//
//class Motorcycle : public Vehicle {
//private:
//    int m_health;
//    bool m_canEvade;
//    sf::SoundBuffer m_engineBuffer;
//    sf::Sound m_engineSound;
//
//    bool loadEngineSound();
//    void applyDamageEffects(int damage);
//
//public:
//    Motorcycle(const sf::Vector2f& position, const std::string& imagePath = "");
//    virtual ~Motorcycle() = default;
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
//    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override;
//
//    void update(float deltaTime) override;
//
//    bool isVehicle() const override { return true; }
//    bool isParkingSpot() const override { return false; }
//    bool isPlayerVehicle() const override { return false; }
//
//    void makeSound() override;
//    int getHealth() const override { return m_health; }
//    void takeDamage(int damage) override;
//    bool isDestroyed() const override { return m_health <= 0; }
//    void repair() override { m_health = 100; }
//    void resetToStartPosition() override;
//
//    void applySpeedBoost(float multiplier, float duration) override;
//    void removeSpeedBoost() override;
//    void applyShield(int protectionLevel) override;
//    void removeShield() override;
//    bool hasShield() const override { return false; }
//    void applyTimeBonus(int bonusTime) override;
//
//    void revEngine();
//    bool canEvadeObstacles() const { return m_canEvade; }
//
//    void handleInput(float deltaTime) override;
//    void moveForward(float deltaTime);
//    void moveBackward(float deltaTime);
//    void turnLeft(float deltaTime);
//    void turnRight(float deltaTime);
//    void emergencyBrake();
//    void releaseControls(float deltaTime);
//};