//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <iostream>
//#include <algorithm>
//#include <SFML/Window/Keyboard.hpp>
//
//#include "Motorcycle.h"
//#include "Constants.h"
//#include "CollisionResult.h"
//#include "Car.h"
//
//Motorcycle::Motorcycle(const sf::Vector2f& position, const std::string& imagePath)
//    : Vehicle(position,
//        imagePath.empty() ? "motorcycle_default" : imagePath,
//        80.0f,
//        15.0f,
//        180.0f)
//    , m_health(100)
//    , m_canEvade(true)
//{
//    if (!loadEngineSound()) {
//        std::cerr << "Warning: Could not load engine sound" << std::endl;
//    }
//
//    std::cout << "Motorcycle created with health: " << m_health << std::endl;
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::acceptCollision(GameObject* other)
//{
//    return std::unique_ptr<CollisionResult>();
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(Car* car) {
//    if (!car) {
//        return CollisionResult::createNoCollision();
//    }
//
//    std::cout << "Motorcycle-to-Car collision detected!" << std::endl;
//
//    const int damage = 30;
//    takeDamage(damage);
//    car->takeDamage(10);
//
//    return std::make_unique<CollisionResult>(
//        CollisionType::MODERATE_DAMAGE,
//        -20,
//        damage,
//        false,
//        EffectType::SPARKS,
//        "Motorcycle hit car - severe damage to motorcycle"
//    );
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(Motorcycle* motorcycle) {
//    if (!motorcycle) {
//        return CollisionResult::createNoCollision();
//    }
//
//    std::cout << "Motorcycle-to-Motorcycle collision detected!" << std::endl;
//
//    const int damage = 15;
//    takeDamage(damage);
//    motorcycle->takeDamage(damage);
//
//    return std::make_unique<CollisionResult>(
//        CollisionType::MINOR_DAMAGE,
//        -10,
//        damage,
//        false,
//        EffectType::SPARKS,
//        "Motorcycle collision - minor scratches"
//    );
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(Truck* truck) {
//    std::cout << "Motorcycle-to-Truck collision detected!" << std::endl;
//
//    takeDamage(100);
//
//    return std::make_unique<CollisionResult>(
//        CollisionType::FATAL_CRASH,
//        -200,
//        100,
//        true,
//        EffectType::EXPLOSION,
//        "Motorcycle vs Truck - fatal collision!"
//    );
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(Vehicle* vehicle) {
//    return std::make_unique<CollisionResult>(
//        CollisionType::MODERATE_DAMAGE,
//        -50,
//        25,
//        false,
//        EffectType::SPARKS,
//        "Motorcycle collided with vehicle"
//    );
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(StaticObstacle* obstacle) {
//    std::cout << "Motorcycle-to-StaticObstacle collision detected!" << std::endl;
//
//    if (m_canEvade && getCurrentSpeed() > 30.0f) {
//        return CollisionResult::createMotorcycleEvadesCone();
//    }
//
//    takeDamage(75);
//    return CollisionResult::createMotorcycleVsParkedCar();
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(DynamicObstacle* obstacle) {
//    std::cout << "Motorcycle-to-DynamicObstacle collision detected!" << std::endl;
//
//    takeDamage(100);
//    return CollisionResult::createFatalCollision();
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(PowerUp* powerUp) {
//    std::cout << "Motorcycle collected PowerUp!" << std::endl;
//
//    return CollisionResult::createPowerUpCollection("Speed Boost");
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(ParkingSpot* parkingSpot) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(RoadBoundary* roadBoundary) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Motorcycle::collideWith(ParkedCar* parkedCar)
//{
//    return CollisionResult::createNoCollision();
//}
//
//void Motorcycle::update(float deltaTime) {
//    if (hasPhysicsBody()) {
//        applyPhysicsConstraints();
//        syncSpriteWithBody();
//    }
//
//    m_canEvade = getCurrentSpeed() > 20.0f;
//
//    static int frameCounter = 0;
//    frameCounter++;
//    if (frameCounter % 180 == 0) {
//        std::cout << "Motorcycle Update - Health: " << m_health
//            << ", Speed: " << getCurrentSpeed()
//            << ", Can Evade: " << (m_canEvade ? "Yes" : "No")
//            << ", Position: (" << getPosition().x << ", " << getPosition().y << ")"
//            << std::endl;
//    }
//}
//
//void Motorcycle::makeSound() {
//    if (m_engineBuffer.getSampleCount() > 0) {
//        m_engineSound.play();
//        std::cout << "Motorcycle engine revved!" << std::endl;
//    }
//    else {
//        std::cout << "Engine sound not available - VROOOM!" << std::endl;
//    }
//}
//
//
//
//void Motorcycle::takeDamage(int damage) {
//    if (damage < 0) damage = 0;
//    if (damage > 100) damage = 100;
//
//    damage *= 2;
//    if (damage > 100) damage = 100;
//
//    m_health -= damage;
//    if (m_health < 0) m_health = 0;
//
//    std::cout << "Motorcycle took " << damage << " damage (doubled vulnerability). Health: " << m_health << std::endl;
//
//    applyDamageEffects(damage);
//}
//
//void Motorcycle::resetToStartPosition()
//{
//    reset();
//    repair();
//}
//
//void Motorcycle::applySpeedBoost(float multiplier, float duration) {
//}
//
//void Motorcycle::removeSpeedBoost() {
//}
//
//void Motorcycle::applyShield(int protectionLevel) {
//}
//
//void Motorcycle::removeShield() {
//}
//
//
//
//void Motorcycle::applyTimeBonus(int bonusTime) {
//}
//
//void Motorcycle::handleInput(float deltaTime) {
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//        moveForward(deltaTime);
//    }
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//        moveBackward(deltaTime);
//    }
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//        emergencyBrake();
//    }
//    else {
//        releaseControls(deltaTime);
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//        turnLeft(deltaTime);
//    }
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//        turnRight(deltaTime);
//    }
//    else {
//        setSteering(0.0f);
//    }
//}
//
//void Motorcycle::moveForward(float deltaTime) {
//    setThrust(getMaxForce());
//}
//
//void Motorcycle::moveBackward(float deltaTime) {
//    setThrust(-getMaxForce() * 0.6f);
//}
//
//void Motorcycle::turnLeft(float deltaTime) {
//    setSteering(-getMaxTorque() * 1.5f);
//}
//
//void Motorcycle::turnRight(float deltaTime) {
//    setSteering(getMaxTorque() * 1.5f);
//}
//
//void Motorcycle::emergencyBrake() {
//    stop();
//    std::cout << "Motorcycle emergency brake applied!" << std::endl;
//}
//
//void Motorcycle::releaseControls(float deltaTime) {
//    setThrust(0.0f);
//}
//
//bool Motorcycle::loadEngineSound() {
//    if (!m_engineBuffer.loadFromFile("resources/sounds/motorcycle-engine.mp3")) {
//        std::cout << "Engine sound file not found - using text engine" << std::endl;
//        return false;
//    }
//
//    m_engineSound.setBuffer(m_engineBuffer);
//    m_engineSound.setVolume(60.0f);
//    std::cout << "Engine sound loaded successfully" << std::endl;
//    return true;
//}
//
//void Motorcycle::applyDamageEffects(int damage) {
//    if (damage > 50) {
//        std::cout << "Motorcycle severely damaged - smoking!" << std::endl;
//    }
//    else if (damage > 20) {
//        std::cout << "Motorcycle moderately damaged!" << std::endl;
//    }
//    else if (damage > 0) {
//        std::cout << "Motorcycle lightly scratched!" << std::endl;
//    }
//}