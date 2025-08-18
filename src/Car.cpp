#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Window/Keyboard.hpp>
#include "SoundManager.h"
#include "Car.h"
#include "Constants.h"
#include "CollisionResult.h"
#include "ParkedCar.h"

Car::Car(const sf::Vector2f& position, const std::string& textureId, float initialAngle)
    : Vehicle(position, textureId,
        Constants::Physics::MAX_VELOCITY,
        Constants::Physics::MAX_ACCELERATION,
        Constants::Physics::STEERING_RATE, initialAngle)
    , m_health(100)
    , m_startPosition(position)
    , m_isMovingForward(false)
    , m_isMovingBackward(false)
    , m_isTurningLeft(false)
    , m_isTurningRight(false)
    , m_hasShield(false)
    , m_shieldLevel(0)
    , m_speedMultiplier(1.0f)
    , m_speedBoostDuration(0.0f)
    , m_isSpeedBoosted(false)
{

}

std::unique_ptr<CollisionResult> Car::collideWith(Car* car) {
    if (!car) {
        return CollisionResult::createNoCollision();
    }

    if (m_hasShield && m_shieldLevel > 0) {
        m_shieldLevel--;
        if (m_shieldLevel <= 0) {
            m_hasShield = false;
        }
        return std::make_unique<CollisionResult>(
            CollisionType::MINOR_DAMAGE,
            -25,
            0,
            false,
            EffectType::SPARKS,
            "Shield absorbed collision with car"
        );
    }

    const int damage = 25;
    takeDamage(damage);

    return std::make_unique<CollisionResult>(
        CollisionType::HEAVY_DAMAGE,
        -100,
        damage,
        true,
        EffectType::CRASH,
        "Hit parked car - returning to start position"
    );
}

std::unique_ptr<CollisionResult> Car::collideWith(ParkedCar* parkedCar) {
    return CollisionResult::createNoCollision();
}



std::unique_ptr<CollisionResult> Car::collideWith(Vehicle* vehicle) {
    return std::make_unique<CollisionResult>(
        CollisionType::MODERATE_DAMAGE,
        -75,
        20,
        true,
        EffectType::SPARKS,
        "Car collided with another vehicle - returning to start"
    );
}

std::unique_ptr<CollisionResult> Car::collideWith(StaticObstacle* obstacle) {
    return std::make_unique<CollisionResult>(
        CollisionType::MINOR_DAMAGE,
        -10,
        10,
        true,
        EffectType::SPARKS,
        "Car hit static obstacle - returning to start"
    );
}

std::unique_ptr<CollisionResult> Car::collideWith(DynamicObstacle* obstacle) {
    if (m_hasShield && m_shieldLevel > 0) {
        m_shieldLevel--;
        if (m_shieldLevel <= 0) {
            m_hasShield = false;
        }
        return std::make_unique<CollisionResult>(
            CollisionType::MINOR_DAMAGE,
            -50,
            10,
            false,
            EffectType::SPARKS,
            "Shield absorbed collision with moving obstacle"
        );
    }

    takeDamage(50);
    return std::make_unique<CollisionResult>(
        CollisionType::HEAVY_DAMAGE,
        -100,
        50,
        true,
        EffectType::CRASH,
        "Car hit moving obstacle - heavy damage!"
    );
}


std::unique_ptr<CollisionResult> Car::collideWith(ParkingSpot* parkingSpot) {
    return CollisionResult::createNoCollision();
}

//std::unique_ptr<CollisionResult> Car::collideWith(RoadBoundary* roadBoundary) {
//    return CollisionResult::createNoCollision();
//}

void Car::resetToStartPosition() {
    resetPhysicsToPosition(m_startPosition);
    stopPhysicsMotion();
    syncSpriteWithBody();
}

void Car::update(float deltaTime) {
    updatePhysics(deltaTime);
    applyPhysicsConstraints();
    syncSpriteWithBody();

    if (m_isSpeedBoosted && m_speedBoostTimer.getElapsedTime().asSeconds() >= m_speedBoostDuration) {
        removeSpeedBoost();
    }
}

void Car::makeSound() {
    SoundManager::getInstance().playSound("drive");

}

void Car::takeDamage(int damage) {
    if (damage < 0) damage = 0;
    if (damage > 100) damage = 100;

    m_health -= damage;
    if (m_health < 0) m_health = 0;

    applyDamageEffects(damage);
}

void Car::applySpeedBoost(float multiplier, float duration) {
    m_speedMultiplier = multiplier;
    m_speedBoostDuration = duration;
    m_isSpeedBoosted = true;
    m_speedBoostTimer.restart();
}

void Car::removeSpeedBoost() {
    m_speedMultiplier = 1.0f;
    m_speedBoostDuration = 0.0f;
    m_isSpeedBoosted = false;
}

void Car::applyShield(int protectionLevel) {
    m_hasShield = true;
    m_shieldLevel = protectionLevel;
}

void Car::removeShield() {
    m_hasShield = false;
    m_shieldLevel = 0;
}

void Car::applyTimeBonus(int bonusTime) {
}

void Car::handleInput(float deltaTime) {
    m_isMovingForward = false;
    m_isMovingBackward = false;
    m_isTurningLeft = false;
    m_isTurningRight = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move(1.0f, deltaTime);
        m_isMovingForward = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        move(-1.0f, deltaTime);
        m_isMovingBackward = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        turn(-1.0f, deltaTime);
        m_isTurningLeft = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        turn(1.0f, deltaTime);
        m_isTurningRight = true;
    }

    if (!m_isMovingForward && !m_isMovingBackward) {
        releaseControls(deltaTime);
    }
}

void Car::move(float direction, float deltaTime) {
    float thrustMultiplier = (direction > 0) ? 1.0f : 0.7f;
    if (m_isSpeedBoosted) {
        thrustMultiplier *= m_speedMultiplier;
    }
    setThrust(direction * getMaxForce() * thrustMultiplier);
}

void Car::turn(float direction, float deltaTime) {
    setSteering(direction * getMaxTorque());
}

void Car::moveForward(float deltaTime) {
    move(1.0f, deltaTime);
}

void Car::moveBackward(float deltaTime) {
    move(-1.0f, deltaTime);
}

void Car::turnLeft(float deltaTime) {
    turn(-1.0f, deltaTime);
}

void Car::turnRight(float deltaTime) {
    turn(1.0f, deltaTime);
}

void Car::emergencyBrake() {
    stop();
}

void Car::releaseControls(float deltaTime) {
    setThrust(0.0f);
}

void Car::updatePhysics(float deltaTime) {
    if (hasPhysicsBody()) {
        applyPhysicsConstraints();
    }
}

void Car::updateRotation() {
    if (hasPhysicsBody()) {
        syncSpriteWithBody();
    }
}



float Car::calculateTurningVelocity() const {
    if (hasPhysicsBody()) {
        return getVelocity().Length();
    }
    return 0.0f;
}

void Car::applyDamageEffects(int damage) {
}