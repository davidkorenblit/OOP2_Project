#include "EffectManager.h"
#include "LevelManager.h"
#include "GameException.h"
#include <iostream>

EffectManager::EffectManager() : m_levelManager(nullptr), m_scoreTimeManager(nullptr) {
}

void EffectManager::setScoreTimeManager(ScoreTimeManager* scoreManager) {
    m_scoreTimeManager = scoreManager;
}

void EffectManager::setLevelManager(LevelManager* levelManager) {
    if (!levelManager) {
        throw EffectProcessingException("Cannot set null LevelManager");
    }
    m_levelManager = levelManager;
}

std::vector<GameAction> EffectManager::processEffectsAndGetActions(const std::vector<std::unique_ptr<CollisionResult>>& results) {
    if (!m_levelManager) {
        throw EffectProcessingException("No LevelManager set for effect processing");
    }

    std::vector<GameAction> actions;

    for (const auto& result : results) {
        if (!result) {
            throw EffectProcessingException("Null collision result found in effect processing");
        }

        applyCollisionResult(*result);

        if (result->shouldRestartLevel()) {
            actions.push_back({ GameAction::RESTART_LEVEL, "Collision requires restart" });
        }

        if (result->getType() == CollisionType::GOAL_REACHED) {
            actions.push_back({ GameAction::NEXT_LEVEL, "Goal reached" });
        }
    }

    return actions;
}

void EffectManager::applyCollisionResult(const CollisionResult& result) {
    if (m_scoreTimeManager && result.getScoreChange() != 0) {
        m_scoreTimeManager->addScore(result.getScoreChange());
        if (result.getEffectType() == EffectType::CRASH) {
            SoundManager::getInstance().stopAllBackgroundSounds();
            SoundManager::getInstance().playSound("crash");
        }
    }
}