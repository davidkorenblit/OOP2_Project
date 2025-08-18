#define _USE_MATH_DEFINES
#include <cmath>
#include "Vehicle.h"
#include "Constants.h"
#include "SoundManager.h"
#include "CollisionResult.h"
#include <iostream>

Vehicle::Vehicle(const sf::Vector2f& position, const std::string& textureId,
    float maxSpeed, float maxForce, float maxTorque, float initialAngle)
    : GameObject(sf::Vector2f(Constants::Physics::PLAYER_WIDTH, Constants::Physics::PLAYER_HEIGHT), textureId)
    , m_body(nullptr)
    , m_world(nullptr)
    , m_maxSpeed(maxSpeed)
    , m_maxForce(maxForce)
    , m_maxTorque(maxTorque)
    , m_currentThrust(0.0f)
    , m_currentSteering(0.0f)
{
    m_sprite.setRotation(initialAngle);
}

Vehicle::~Vehicle() {
    destroyPhysicsBody();
}

std::unique_ptr<CollisionResult> Vehicle::acceptCollision(GameObject* other) {
    if (!other) {
        return CollisionResult::createNoCollision();
    }
    return other->collideWith(this);
}

void Vehicle::createPhysicsBody(b2World* world, const sf::Vector2f& position, float angle) {
    if (m_body) {
        destroyPhysicsBody();
    }

    m_world = world;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = sfmlToBox2D(position);
    bodyDef.angle = angle * M_PI / 180.0f;
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    float halfWidth = (Constants::Physics::PLAYER_WIDTH / 2.0f) / PIXELS_PER_METER;
    float halfHeight = (Constants::Physics::PLAYER_HEIGHT / 2.0f) / PIXELS_PER_METER;
    shape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.8f;
    fixtureDef.restitution = 0.2f;

    m_body->CreateFixture(&fixtureDef);

    m_body->SetLinearDamping(2.0f);
    m_body->SetAngularDamping(3.0f);
}

void Vehicle::destroyPhysicsBody() {
    if (m_body && m_world) {
        m_world->DestroyBody(m_body);
        m_body = nullptr;
        m_world = nullptr;
    }
}

sf::Vector2f Vehicle::getPosition() const {
    return box2DToSFML(m_body->GetPosition());
}

void Vehicle::setPosition(const sf::Vector2f& position) {
    if (m_body) {
        m_body->SetTransform(sfmlToBox2D(position), m_body->GetAngle());
    }
	m_sprite.setPosition(position);
}

const b2Vec2& Vehicle::getVelocity() const {
    static b2Vec2 zeroVel(0.0f, 0.0f);
    if (!m_body) {
        return zeroVel;
    }
    return m_body->GetLinearVelocity();
}

float Vehicle::getCurrentSpeed() const {
    if (!m_body) {
        return 0.0f;
    }
    b2Vec2 vel = m_body->GetLinearVelocity();
    return std::sqrt(vel.x * vel.x + vel.y * vel.y) * PIXELS_PER_METER;
}

float Vehicle::getRotationAngle() const {
    if (!m_body) {
        return Constants::Physics::PLAYER_INIT_ROTATION;
    }
    return m_body->GetAngle() * 180.0f / M_PI;
}

void Vehicle::setThrust(float thrust) {
    m_currentThrust = clamp(thrust, -m_maxForce, m_maxForce);

    if (m_body) {
        b2Vec2 forwardDir = m_body->GetWorldVector(b2Vec2(1.0f, 0.0f));
        b2Vec2 force = m_currentThrust * forwardDir;

        m_body->ApplyForceToCenter(force, true);
    }
    if (std::abs(thrust) > 0.1f && getCurrentSpeed() > MOVEMENT_THRESHOLD) {
        SoundManager::getInstance().switchBackgroundLoop("drive");
    }
   /* else if (std::abs(thrust) <= 0.1f) {
        SoundManager::getInstance().stopAllBackgroundSounds();
    }*/
}

void Vehicle::setSteering(float steering) {
    m_currentSteering = clamp(steering, -m_maxTorque, m_maxTorque);

    if (m_body && getCurrentSpeed() > MOVEMENT_THRESHOLD) {
        b2Vec2 rightDir = m_body->GetWorldVector(b2Vec2(1.0f, 0.0f));
        float steeringForce = m_currentSteering * 0.5f;
        b2Vec2 force = steeringForce * rightDir;

        float halfHeight = (Constants::Physics::PLAYER_HEIGHT / 2.0f) / PIXELS_PER_METER;
        b2Vec2 frontAxleOffset(0.0f, -halfHeight * 0.6f);
        b2Vec2 frontAxlePoint = m_body->GetWorldPoint(frontAxleOffset);

        m_body->ApplyForce(force, frontAxlePoint, true);
    }
}

void Vehicle::applyForce(const sf::Vector2f& force) {
    if (m_body) {
        b2Vec2 box2dForce = sfmlToBox2D(force);
        box2dForce.x /= PIXELS_PER_METER;
        box2dForce.y /= PIXELS_PER_METER;
        m_body->ApplyForceToCenter(box2dForce, true);
    }
}

void Vehicle::applyTorque(float torque) {
    if (m_body) {
        m_body->ApplyTorque(torque, true);
    }
}

void Vehicle::stop() {
    if (m_body) {
        m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        m_body->SetAngularVelocity(0.0f);
    }
    m_currentThrust = 0.0f;
    m_currentSteering = 0.0f;
    //SoundManager::getInstance().stopAllBackgroundSounds();

}

void Vehicle::reset() {
    stop();
    if (m_body) {
        m_body->SetTransform(sfmlToBox2D(Constants::getStartPosition()),
            Constants::Physics::PLAYER_INIT_ROTATION * M_PI / 180.0f);
    }
}

bool Vehicle::isMoving() const {
    return getCurrentSpeed() > MOVEMENT_THRESHOLD;
}

bool Vehicle::isMovingForward() const {
    if (!m_body) return false;

    b2Vec2 velocity = m_body->GetLinearVelocity();
    b2Vec2 forward = m_body->GetWorldVector(b2Vec2(1.0f, 0.0f));

    float dot = velocity.x * forward.x + velocity.y * forward.y;
    return dot > MOVEMENT_THRESHOLD / PIXELS_PER_METER;
}

bool Vehicle::isMovingBackward() const {
    if (!m_body) return false;

    b2Vec2 velocity = m_body->GetLinearVelocity();
    b2Vec2 forward = m_body->GetWorldVector(b2Vec2(0.0f, -1.0f));

    float dot = velocity.x * forward.x + velocity.y * forward.y;
    return dot < -MOVEMENT_THRESHOLD / PIXELS_PER_METER;
}

bool Vehicle::isTurning() const {
    if (!m_body) return false;
    return std::abs(m_body->GetAngularVelocity()) > ANGLE_THRESHOLD;
}

void Vehicle::applyPhysicsConstraints() {
    if (!m_body) return;

    b2Vec2 velocity = m_body->GetLinearVelocity();
    float speed = velocity.Length();
    float maxSpeedBox2D = m_maxSpeed / PIXELS_PER_METER;

    if (speed > maxSpeedBox2D) {
        velocity.Normalize();
        velocity *= maxSpeedBox2D;
        m_body->SetLinearVelocity(velocity);
    }
}

void Vehicle::syncSpriteWithBody() {
    if (m_body) {
        sf::Vector2f position = getPosition();
        float angle = getRotationAngle();

        m_sprite.setPosition(position);
        m_sprite.setRotation(angle);
    }
}

float Vehicle::clamp(float value, float min, float max) const {
    return std::max(min, std::min(value, max));
}

b2Vec2 Vehicle::sfmlToBox2D(const sf::Vector2f& sfmlVec) const {
  
    return b2Vec2(sfmlVec.x / PIXELS_PER_METER, sfmlVec.y / PIXELS_PER_METER);
}

sf::Vector2f Vehicle::box2DToSFML(const b2Vec2& box2dVec) const {
    return sf::Vector2f(box2dVec.x * PIXELS_PER_METER, box2dVec.y * PIXELS_PER_METER);
}

void Vehicle::resetPhysicsToPosition(const sf::Vector2f& position) {
    if (m_body) {
        m_body->SetTransform(sfmlToBox2D(position), 0.0f);
        m_body->SetAwake(true);
    }
}

void Vehicle::stopPhysicsMotion() {
    if (m_body) {
        m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        m_body->SetAngularVelocity(0.0f);
    }
}