//#include "SpeedBoost.h"
//#include "Vehicle.h"
//#include "Car.h"
//#include "Motorcycle.h"
//
//SpeedBoost::SpeedBoost(const sf::Vector2f& position, float duration)
//    : PowerUp(position, sf::Vector2f(32.0f, 32.0f), "assets/speedBoost.png", 100)
//    , m_speedMultiplier(1.5f)
//    , m_originalMaxSpeed(0.0f) {
//    m_duration = duration;
//}
//
//void SpeedBoost::activate(Vehicle* vehicle) {
//    m_originalMaxSpeed = vehicle->getMaxSpeed();
//    m_speedMultiplier = 1.5f;
//
//    vehicle->applySpeedBoost(m_speedMultiplier, m_duration);
//}
//
//void SpeedBoost::deactivate(Vehicle* vehicle) {
//    vehicle->removeSpeedBoost();
//}