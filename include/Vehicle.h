#pragma once
#include "GameObject.h"
#include <SFML/System/Vector2.hpp>
#include <box2d/box2d.h>


class ParkedCar;

class Vehicle : public GameObject {
private:
    b2Body* m_body;
    b2World* m_world;

    float m_maxSpeed;
    float m_maxForce;
    float m_maxTorque;
    float m_currentThrust;
    float m_currentSteering;

    static constexpr float MOVEMENT_THRESHOLD = 1.0f;
    static constexpr float ANGLE_THRESHOLD = 0.8f;
    static constexpr float PIXELS_PER_METER = 16.0f;

    float clamp(float value, float min, float max) const;
    b2Vec2 sfmlToBox2D(const sf::Vector2f& sfmlVec) const;
    sf::Vector2f box2DToSFML(const b2Vec2& box2dVec) const;

protected:
    void applyPhysicsConstraints();
    void syncSpriteWithBody();
    void resetPhysicsToPosition(const sf::Vector2f& position);
    void stopPhysicsMotion();

public:
    Vehicle(const sf::Vector2f& position, const std::string& textureId,
        float maxSpeed = 60.0f, float maxForce = 50.0f, float maxTorque = 30.0f, float initialAngle = 180.0f);
    virtual ~Vehicle();

    void createPhysicsBody(b2World* world, const sf::Vector2f& position, float angle = 180.0f);
    void destroyPhysicsBody();

    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f& position) override;
    //sf::FloatRect getBounds() const override;

    std::unique_ptr<CollisionResult> acceptCollision(GameObject* other) override;
    std::unique_ptr<CollisionResult> collideWith(Car* car) override = 0;
    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override = 0;
    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override = 0;
    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override = 0;
    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override = 0;
    //std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override = 0;
    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override = 0;

    bool isVehicle() const override { return true; }
    bool isParkingSpot() const override { return false; }
    bool isPlayerVehicle() const override { return false; }

    const b2Vec2& getVelocity() const;
    float getCurrentSpeed() const;
    float getRotationAngle() const;
    float getMaxSpeed() const { return m_maxSpeed; }
    float getMaxForce() const { return m_maxForce; }
    float getMaxTorque() const { return m_maxTorque; }

    void setThrust(float thrust);
    void setSteering(float steering);
    void applyForce(const sf::Vector2f& force);
    void applyTorque(float torque);
    virtual void stop();
    virtual void reset();

    bool isMoving() const;
    bool isMovingForward() const;
    bool isMovingBackward() const;
    bool isTurning() const;
    bool hasPhysicsBody() const { return m_body != nullptr; }

    virtual void handleInput(float deltaTime) = 0;
    virtual void makeSound() = 0;
    virtual int getHealth() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual bool isDestroyed() const = 0;
    virtual void repair() = 0;
    virtual void resetToStartPosition() = 0;

    virtual void applySpeedBoost(float multiplier, float duration) = 0;
    virtual void removeSpeedBoost() = 0;
    virtual void applyShield(int protectionLevel) = 0;
    virtual void removeShield() = 0;
    virtual bool hasShield() const = 0;
    virtual void applyTimeBonus(int bonusTime) = 0;

    void update(float deltaTime) override = 0;
};