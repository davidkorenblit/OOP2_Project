//#pragma once
//#include "PowerUp.h"
//
//class Shield : public PowerUp {
//private:
//    int m_protectionLevel;
//    bool m_isProtecting;
//
//public:
//    Shield(const sf::Vector2f& position, int protectionLevel = 1);
//    ~Shield() override = default;
//
//    void activate(Vehicle* vehicle) override;
//    void deactivate(Vehicle* vehicle) override;
//
//    bool isProtecting() const { return m_isProtecting; }
//    void useProtection();
//    int getProtectionLevel() const { return m_protectionLevel; }
//};