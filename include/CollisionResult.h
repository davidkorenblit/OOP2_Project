#pragma once
#include <string>
#include <memory>

enum class CollisionType {
    NONE,
    MINOR_DAMAGE,
    MODERATE_DAMAGE,
    HEAVY_DAMAGE,
    FATAL_CRASH,
    BONUS_COLLECTED,
    GOAL_REACHED,
    TRAFFIC_VIOLATION,
    EVASION_SUCCESS
};

enum class EffectType {
    NONE,
    EXPLOSION,
    SPARKS,
    HONK,
    COLLECT_SOUND,
    SCREECH,
    CRASH
};

class CollisionResult {
private:
    CollisionType m_type;
    int m_scoreChange;
    int m_damage;
    bool m_shouldRestart;
    EffectType m_effectType;
    std::string m_message;

public:
    CollisionResult();
    CollisionResult(CollisionType type, int scoreChange, int damage);
    CollisionResult(CollisionType type, int scoreChange, int damage,
        bool shouldRestart, EffectType effectType, const std::string& message);

    CollisionType getType() const { return m_type; }
    int getScoreChange() const { return m_scoreChange; }
    int getDamage() const { return m_damage; }
    bool shouldRestartLevel() const { return m_shouldRestart; }
    EffectType getEffectType() const { return m_effectType; }
    const std::string& getMessage() const { return m_message; }
    bool hasCollision() const { return m_type != CollisionType::NONE; }
    bool isFatal() const { return m_type == CollisionType::FATAL_CRASH || m_shouldRestart; }

    static std::unique_ptr<CollisionResult> createNoCollision();
    static std::unique_ptr<CollisionResult> createCarVsParkedCar();
    static std::unique_ptr<CollisionResult> createMotorcycleVsParkedCar();
    static std::unique_ptr<CollisionResult> createTruckVsParkedCar();
    static std::unique_ptr<CollisionResult> createVehicleVsSidewalk(bool isHeavyVehicle = false);
    static std::unique_ptr<CollisionResult> createMotorcycleEvadesCone();
    static std::unique_ptr<CollisionResult> createVehicleVsTrafficCone(bool isMotorcycleEvasion = false);
    static std::unique_ptr<CollisionResult> createFatalCollision();
    static std::unique_ptr<CollisionResult> createPowerUpCollection(const std::string& bonusType);

    std::string getTypeString() const;
    std::string getDebugInfo() const;
};