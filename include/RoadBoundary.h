//#pragma once
//#include "GameObject.h"
//
//class RoadBoundary : public GameObject {
//private:
//    float m_width;
//    float m_height;
//
//public:
//    RoadBoundary(const sf::Vector2f& position, float width, float height);
//    virtual ~RoadBoundary() = default;
//
//    std::unique_ptr<CollisionResult> acceptCollision(GameObject* other) override;
//    std::unique_ptr<CollisionResult> collideWith(Car* car) override;
//    std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) override;
//    std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) override;
//    std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) override;
//    std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) override;
//    std::unique_ptr<CollisionResult> collideWith(RoadBoundary* roadBoundary) override;
//    std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) override;
//
//    void update(float deltaTime) override;
//
//    bool isVehicle() const override { return false; }
//    bool isParkingSpot() const override { return false; }
//    bool isPlayerVehicle() const override { return false; }
//    float getWidth() const { return m_width; }
//    float getHeight() const { return m_height; }
//
//};