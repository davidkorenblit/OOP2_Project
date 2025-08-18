//#include "Shield.h"
//#include "Vehicle.h"
//#include "Car.h"
//#include "Motorcycle.h"
//
//Shield::Shield(const sf::Vector2f& position, int protectionLevel)
//    : PowerUp(position, sf::Vector2f(32.0f, 32.0f), "assets/shield.png", 100)
//    , m_protectionLevel(protectionLevel)
//    , m_isProtecting(false) {
//
//    m_duration = 0.0f;
//}
//
//void Shield::activate(Vehicle* vehicle) {
//    m_isProtecting = true;
//    m_protectionLevel = 1;
//    m_duration = 0.0f;
//
//    vehicle->applyShield(m_protectionLevel);
//}
//
//void Shield::deactivate(Vehicle* vehicle) {
//    m_isProtecting = false;
//    vehicle->removeShield();
//}
//
//void Shield::useProtection() {
//    if (m_isProtecting && m_protectionLevel > 0) {
//        m_protectionLevel--;
//        if (m_protectionLevel <= 0) {
//            m_isProtecting = false;
//        }
//    }
//}