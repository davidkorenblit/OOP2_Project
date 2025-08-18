#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class CollisionResult;
class Car;
class Vehicle;
class StaticObstacle;
class DynamicObstacle;
class ParkingSpot;
class RoadBoundary;
class ParkedCar;

class GameObject {
private:
    static int s_nextId;
    int m_id;

protected:
    sf::Vector2f m_size;
    sf::Sprite m_sprite;

    void setScale(float scale);
    void setTextureFromManager(const std::string& textureId);

public:
    GameObject(const sf::Vector2f& size, const std::string& textureId = "");
    virtual ~GameObject() = default;

    virtual std::unique_ptr<CollisionResult> acceptCollision(GameObject* other) = 0;
    virtual std::unique_ptr<CollisionResult> collideWith(Car* car) = 0;
    virtual std::unique_ptr<CollisionResult> collideWith(Vehicle* vehicle) = 0;
    virtual std::unique_ptr<CollisionResult> collideWith(StaticObstacle* obstacle) = 0;
    virtual std::unique_ptr<CollisionResult> collideWith(DynamicObstacle* obstacle) = 0;
    virtual std::unique_ptr<CollisionResult> collideWith(ParkingSpot* parkingSpot) = 0;
    virtual std::unique_ptr<CollisionResult> collideWith(ParkedCar* parkedCar) = 0;

    virtual void update(float deltaTime) = 0;
    virtual sf::Vector2f getPosition() const
    {
        return m_sprite.getPosition();
    }
    virtual void setPosition(const sf::Vector2f& position) {
        m_sprite.setPosition(position);
    }
    sf::FloatRect getBounds() const;
    virtual bool isVehicle() const = 0;
    virtual bool isParkingSpot() const = 0;
    virtual bool isPlayerVehicle() const = 0;

    bool isColliding(const GameObject& other) const;
    int getId() const { return m_id; }
    const sf::Vector2f& getSize() const { return m_size; }
    void draw(sf::RenderWindow& window) const;

    sf::Sprite& getSprite() { return m_sprite; }
    const sf::Sprite& getSprite() const { return m_sprite; }
    void setRotation(float angle) { m_sprite.setRotation(angle); }

};