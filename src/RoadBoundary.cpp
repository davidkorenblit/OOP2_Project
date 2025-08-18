//#include "RoadBoundary.h"
//#include "CollisionResult.h"
//#include "Car.h"    
//#include <iostream>
//
//RoadBoundary::RoadBoundary(const sf::Vector2f& position, float width, float height)
//    : GameObject(sf::Vector2f(width, height), "blank")
//    , m_width(width)
//    , m_height(height)
//{
//    setPosition(position);
//}
//
//std::unique_ptr<CollisionResult> RoadBoundary::acceptCollision(GameObject* other) {
//    return other->collideWith(this);
//}
//
//std::unique_ptr<CollisionResult> RoadBoundary::collideWith(Car* car) {
//    return std::make_unique<CollisionResult>(
//        CollisionType::TRAFFIC_VIOLATION,
//        -25,
//        0,
//        true,
//        EffectType::NONE,
//        "Car hit boundary - reset to start"
//    );
//}
//
//
//
//std::unique_ptr<CollisionResult> RoadBoundary::collideWith(Vehicle* vehicle) {
//    return std::make_unique<CollisionResult>(
//        CollisionType::TRAFFIC_VIOLATION,
//        -30,
//        0,
//        true,
//        EffectType::NONE,
//        "Vehicle hit road boundary"
//    );
//}
//
//std::unique_ptr<CollisionResult> RoadBoundary::collideWith(StaticObstacle* obstacle) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> RoadBoundary::collideWith(DynamicObstacle* obstacle) {
//    return CollisionResult::createNoCollision();
//}
//
//
//
//std::unique_ptr<CollisionResult> RoadBoundary::collideWith(ParkingSpot* parkingSpot) {
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> RoadBoundary::collideWith(RoadBoundary* roadBoundary)
//{
//    return CollisionResult::createNoCollision();
//}
//
//std::unique_ptr<CollisionResult> RoadBoundary::collideWith(ParkedCar* parkedCar)
//{
//    return CollisionResult::createNoCollision();
//}
//
//void RoadBoundary::update(float deltaTime) {
//}
//
//
//
