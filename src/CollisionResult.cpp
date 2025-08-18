#include "CollisionResult.h"
#include <sstream>

CollisionResult::CollisionResult()
    : m_type(CollisionType::NONE)
    , m_scoreChange(0)
    , m_damage(0)
    , m_shouldRestart(false)
    , m_effectType(EffectType::NONE)
    , m_message("No collision")
{
}

CollisionResult::CollisionResult(CollisionType type, int scoreChange, int damage)
    : m_type(type)
    , m_scoreChange(scoreChange)
    , m_damage(damage)
    , m_shouldRestart(type == CollisionType::FATAL_CRASH)
    , m_effectType(EffectType::NONE)
    , m_message("Collision occurred")
{
    switch (type) {
    case CollisionType::FATAL_CRASH:
        m_effectType = EffectType::EXPLOSION;
        m_message = "Fatal collision!";
        break;
    case CollisionType::HEAVY_DAMAGE:
        m_effectType = EffectType::CRASH;
        m_message = "Heavy damage sustained";
        break;
    case CollisionType::MODERATE_DAMAGE:
        m_effectType = EffectType::SPARKS;
        m_message = "Moderate damage";
        break;
    case CollisionType::MINOR_DAMAGE:
        m_effectType = EffectType::SPARKS;
        m_message = "Minor damage";
        break;
    case CollisionType::BONUS_COLLECTED:
        m_effectType = EffectType::COLLECT_SOUND;
        m_message = "Bonus collected!";
        break;
    case CollisionType::TRAFFIC_VIOLATION:
        m_effectType = EffectType::HONK;
        m_message = "Traffic violation";
        break;
    default:
        break;
    }
}

CollisionResult::CollisionResult(CollisionType type, int scoreChange, int damage,
    bool shouldRestart, EffectType effectType, const std::string& message)
    : m_type(type)
    , m_scoreChange(scoreChange)
    , m_damage(damage)
    , m_shouldRestart(shouldRestart)
    , m_effectType(effectType)
    , m_message(message)
{
}

std::unique_ptr<CollisionResult> CollisionResult::createNoCollision() {
    return std::make_unique<CollisionResult>();
}

std::unique_ptr<CollisionResult> CollisionResult::createCarVsParkedCar() {
    return std::make_unique<CollisionResult>(
        CollisionType::HEAVY_DAMAGE,
        -100,
        50,
        true,
        EffectType::CRASH,
        "Car hit parked vehicle - heavy damage!"
    );
}

//std::unique_ptr<CollisionResult> CollisionResult::createMotorcycleVsParkedCar() {
//    return std::make_unique<CollisionResult>(
//        CollisionType::HEAVY_DAMAGE,
//        -150,
//        75,
//        false,
//        EffectType::CRASH,
//        "Motorcycle crashed into parked car - very heavy damage!"
//    );
//}
//
//std::unique_ptr<CollisionResult> CollisionResult::createTruckVsParkedCar() {
//    return std::make_unique<CollisionResult>(
//        CollisionType::FATAL_CRASH,
//        -200,
//        100,
//        true,
//        EffectType::EXPLOSION,
//        "Truck destroyed parked car - complete destruction!"
//    );
//}

std::unique_ptr<CollisionResult> CollisionResult::createVehicleVsSidewalk(bool isHeavyVehicle) {
    int penalty = isHeavyVehicle ? -50 : -25;
    std::string message = isHeavyVehicle ?
        "Heavy vehicle on sidewalk - serious violation!" :
        "Driving on sidewalk - traffic violation!";

    return std::make_unique<CollisionResult>(
        CollisionType::TRAFFIC_VIOLATION,
        penalty,
        0,
        false,
        EffectType::HONK,
        message
    );
}

//std::unique_ptr<CollisionResult> CollisionResult::createMotorcycleEvadesCone() {
//    return std::make_unique<CollisionResult>(
//        CollisionType::EVASION_SUCCESS,
//        5,
//        0,
//        false,
//        EffectType::COLLECT_SOUND,
//        "Motorcycle successfully evaded traffic cone!"
//    );
//}

//std::unique_ptr<CollisionResult> CollisionResult::createVehicleVsTrafficCone(bool isMotorcycleEvasion) {
//    if (isMotorcycleEvasion) {
//        return createMotorcycleEvadesCone();
//    }
//
//    return std::make_unique<CollisionResult>(
//        CollisionType::MINOR_DAMAGE,
//        -10,
//        10,
//        false,
//        EffectType::SPARKS,
//        "Hit traffic cone"
//    );
//}

std::unique_ptr<CollisionResult> CollisionResult::createFatalCollision() {
    return std::make_unique<CollisionResult>(
        CollisionType::FATAL_CRASH,
        -200,
        100,
        true,
        EffectType::EXPLOSION,
        "Fatal collision with pedestrian - level restart required!"
    );
}
//
//std::unique_ptr<CollisionResult> CollisionResult::createPowerUpCollection(const std::string& bonusType) {
//    std::string message = "Collected " + bonusType + " power-up!";
//
//    return std::make_unique<CollisionResult>(
//        CollisionType::BONUS_COLLECTED,
//        100,
//        0,
//        false,
//        EffectType::COLLECT_SOUND,
//        message
//    );
//}

std::string CollisionResult::getTypeString() const {
    switch (m_type) {
    case CollisionType::NONE: return "NONE";
    case CollisionType::MINOR_DAMAGE: return "MINOR_DAMAGE";
    case CollisionType::MODERATE_DAMAGE: return "MODERATE_DAMAGE";
    case CollisionType::HEAVY_DAMAGE: return "HEAVY_DAMAGE";
    case CollisionType::FATAL_CRASH: return "FATAL_CRASH";
    case CollisionType::BONUS_COLLECTED: return "BONUS_COLLECTED";
    case CollisionType::GOAL_REACHED: return "GOAL_REACHED";
    case CollisionType::TRAFFIC_VIOLATION: return "TRAFFIC_VIOLATION";
    case CollisionType::EVASION_SUCCESS: return "EVASION_SUCCESS";
    default: return "UNKNOWN";
    }
}

std::string CollisionResult::getDebugInfo() const {
    std::ostringstream oss;
    oss << "CollisionResult {"
        << " Type: " << getTypeString()
        << ", Score: " << m_scoreChange
        << ", Damage: " << m_damage
        << ", Restart: " << (m_shouldRestart ? "YES" : "NO")
        << ", Message: '" << m_message << "'"
        << " }";
    return oss.str();
}