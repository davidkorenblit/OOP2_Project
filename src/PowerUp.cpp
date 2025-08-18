//#include "PowerUp.h"
//#include "Vehicle.h"
//#include "CollisionResult.h"
//#include "Car.h"
//#include "Truck.h"
//#include "GameObject.h"
//#include "Motorcycle.h"
//
//PowerUp::PowerUp(const sf::Vector2f& position, const sf::Vector2f& size,
//    const std::string& texturePath, int scoreValue)
//    : GameObject(size, texturePath)
//    , m_isCollected(false)
//    , m_scoreValue(scoreValue)
//    , m_duration(0.0f)
//    , m_isActive(false) {
//    setPosition(position);
//}
//
//std::unique_ptr<CollisionResult> PowerUp::acceptCollision(GameObject* other) {
//    return other->collideWith(this);
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(Car* car) {
//    if (!m_isCollected) {
//        collect();
//        activate(car);
//        return std::make_unique<CollisionResult>(
//            CollisionType::BONUS_COLLECTED,
//            m_scoreValue,
//            0,
//            false,
//            EffectType::COLLECT_SOUND,
//            "Car collected power-up!"
//        );
//    }
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(Motorcycle* motorcycle) {
//    if (!m_isCollected) {
//        collect();
//        activate(motorcycle);
//        return std::make_unique<CollisionResult>(
//            CollisionType::BONUS_COLLECTED,
//            m_scoreValue,
//            0,
//            false,
//            EffectType::COLLECT_SOUND,
//            "Motorcycle collected power-up!"
//        );
//    }
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(Truck* truck) {
//    if (!m_isCollected) {
//        collect();
//        activate(truck);
//        return std::make_unique<CollisionResult>(
//            CollisionType::BONUS_COLLECTED,
//            m_scoreValue,
//            0,
//            false,
//            EffectType::COLLECT_SOUND,
//            "Truck collected power-up!"
//        );
//    }
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(Vehicle* vehicle) {
//    if (!m_isCollected) {
//        collect();
//        activate(vehicle);
//        return std::make_unique<CollisionResult>(
//            CollisionType::BONUS_COLLECTED,
//            m_scoreValue,
//            0,
//            false,
//            EffectType::COLLECT_SOUND,
//            "Vehicle collected power-up!"
//        );
//    }
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(StaticObstacle* obstacle) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(DynamicObstacle* obstacle) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(PowerUp* powerup) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(ParkingSpot* parkingSpot) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> PowerUp::collideWith(RoadBoundary* roadBoundary) {
//    return CollisionResult::createNoCollision();
//}
//
//void PowerUp::update(float deltaTime) {
//    if (m_isActive && m_duration > 0.0f && isExpired()) {
//        m_isActive = false;
//    }
//}
//
//sf::Vector2f PowerUp::getPosition() const {
//    return getTransform().transformPoint(0, 0);
//}
//
//void PowerUp::setPosition(const sf::Vector2f& position) {
//    sf::Transformable::setPosition(position);
//    m_sprite.setPosition(position);
//}
//
//sf::FloatRect PowerUp::getBounds() const {
//    return getTransform().transformRect(m_sprite.getLocalBounds());
//}
//
//void PowerUp::collect() {
//    m_isCollected = true;
//    m_isActive = true;
//    m_activationTimer.restart();
//}
//
//bool PowerUp::isExpired() const {
//    return m_duration > 0.0f && m_activationTimer.getElapsedTime().asSeconds() >= m_duration;
//}