//#include "Truck.h"
//#include "CollisionResult.h"
//
//Truck::Truck(const sf::Vector2f& position, const std::string& textureId)
//    : Vehicle(position, textureId, 40.0f, 80.0f, 25.0f)
//    , m_health(150) {
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(Car* car) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(Motorcycle* motorcycle) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(Truck* truck) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(Vehicle* vehicle) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(StaticObstacle* obstacle) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(DynamicObstacle* obstacle) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(PowerUp* powerup) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(ParkingSpot* parkingSpot) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> Truck::collideWith(RoadBoundary* roadBoundary) {
//    return CollisionResult::createNoCollision();
//}
//
//void Truck::update(float deltaTime) {
//}
//
//void Truck::handleInput(float deltaTime) {
//}
//
//void Truck::makeSound() {
//}
//
//int Truck::getHealth() const {
//    return m_health;
//}
//
//void Truck::takeDamage(int damage) {
//    m_health -= damage;
//    if (m_health < 0) m_health = 0;
//}
//
//bool Truck::isDestroyed() const {
//    return m_health <= 0;
//}
//
//void Truck::repair() {
//    m_health = 150;
//}
//
//void Truck::resetToStartPosition() {
//    reset();
//    repair();
//}
//
//void Truck::applySpeedBoost(float multiplier, float duration) {
//}
//
//void Truck::removeSpeedBoost() {
//}
//
//void Truck::applyShield(int protectionLevel) {
//}
//
//void Truck::removeShield() {
//}
//
//bool Truck::hasShield() const {
//    return false;
//}
//
//void Truck::applyTimeBonus(int bonusTime) {
//}