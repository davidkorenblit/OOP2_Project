#pragma once
#include <vector>
#include <memory>
#include "CollisionResult.h"
#include "ScoreTimeManager.h"
#include "SoundManager.h"

class LevelManager;

struct GameAction {
    enum Type { RESTART_LEVEL, NEXT_LEVEL, NONE };
    Type action = NONE;
    std::string reason;
};

class EffectManager {
private:
    LevelManager* m_levelManager;
    ScoreTimeManager* m_scoreTimeManager;

public:
    EffectManager();
    ~EffectManager() = default;
    void setScoreTimeManager(ScoreTimeManager* scoreManager);
    void setLevelManager(LevelManager* levelManager);
    std::vector<GameAction> processEffectsAndGetActions(const std::vector<std::unique_ptr<CollisionResult>>& results);

private:
    void applyCollisionResult(const CollisionResult& result);
};