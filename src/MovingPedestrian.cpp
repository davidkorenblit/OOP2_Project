//#include "MovingPedestrian.h"
//#include "CollisionResult.h"
//#include "Constants.h"
//
//MovingPedestrian::MovingPedestrian(const sf::Vector2f& startPosition, const sf::Vector2f& direction,
//    float speed, float respawnDelay)
//    : DynamicObstacle(startPosition, direction, speed, respawnDelay,
//        sf::Vector2f(30.0f, 60.0f), "pedestrian")
//{
//}
//
//std::unique_ptr<CollisionResult> MovingPedestrian::collideWith(Car* car) {
//    return CollisionResult::createFatalCollision();
//}
//
//std::unique_ptr<CollisionResult> MovingPedestrian::collideWith(Motorcycle* motorcycle) {
//    return CollisionResult::createFatalCollision();
//}
//
//std::unique_ptr<CollisionResult> MovingPedestrian::collideWith(Truck* truck) {
//    return CollisionResult::createFatalCollision();
//}