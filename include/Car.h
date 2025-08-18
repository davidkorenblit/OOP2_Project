#pragma once
#include "Vehicle.h"
#include "StaticObstacle.h"
#include "DynamicObstacle.h"
#include "PowerUp.h"
#include "ParkingSpot.h"
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>

class ParkedCar;

class Car : public Vehicle {
private:
    int m_health;
    sf::Vector2f m_startPosition;
 /*   sf::SoundBuffer m_honkBuffer;
    sf::Sound m_honkSound;*/
    bool m_isMovingForward;
    bool m_isMovingBackward;
    bool m_isTurningLeft;
    bool m_isTurningRight;

    bool m_hasShield;
    int m_shieldLevel;
    float m_speedMultiplier;
    sf::Clock m_speedBoostTimer;
    float m_speedBoostDuration;
    bool m_isSpeedBoosted;

    float calculateTurningVelocity() const;
    void applyDamageEffects(int damage);

protected:
    void updatePhysics(float deltaTime);
    void updateRotation();

public:
    Car(const sf::Vector2f& position, const std::string& textureId = "car_default", float initialAngle = 180.0f);    virtual ~Car() = default;
    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override;
    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override;
    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override;
    //std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override;
    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override;

    void update(float deltaTime) override;

    void makeSound() override;
    int getHealth() const override { return m_health; }
    void takeDamage(int damage) override;
    bool isDestroyed() const override { return m_health <= 0; }
    void repair() override { m_health = 100; }
    void resetToStartPosition() override;

    void applySpeedBoost(float multiplier, float duration) override;
    void removeSpeedBoost() override;
    void applyShield(int protectionLevel) override;
    void removeShield() override;
    bool hasShield() const override { return m_hasShield; }
    void applyTimeBonus(int bonusTime) override;

    bool isPlayerVehicle() const override { return true; }

    void handleInput(float deltaTime) override;
    void move(float direction, float deltaTime);
    void turn(float direction, float deltaTime);
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void turnLeft(float deltaTime);
    void turnRight(float deltaTime);
    void emergencyBrake();
    void releaseControls(float deltaTime);
};