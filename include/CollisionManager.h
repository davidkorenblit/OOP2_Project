//#pragma once
//#include <vector>
//#include <memory>
//#include "GameObject.h"
//#include "CollisionResult.h"
//
//class LevelManager;
//
//class CollisionManager {
//private:
//    std::vector<std::unique_ptr<CollisionResult>> m_collisionHistory;
//    LevelManager* m_levelManager;
//    bool m_needsPlayerReset;
//    bool m_gameWon = false;
//    bool areObjectsColliding(GameObject* obj1, GameObject* obj2);
//    void applyCollisionResult(const CollisionResult& result);
//
//public:
//    CollisionManager();
//    ~CollisionManager() = default;
//    bool isGameWon() const { return m_gameWon; }
//    void resetGameState() { m_gameWon = false; }
//    void setLevelManager(LevelManager* levelManager) { m_levelManager = levelManager; }
//    void checkCollisions(const std::vector<GameObject*>& objects);
//    void processDelayedActions();
//
//    const std::vector<std::unique_ptr<CollisionResult>>& getCollisionHistory() const {
//        return m_collisionHistory;
//    }
//    void clearHistory() { m_collisionHistory.clear(); }
//
//    int getTotalScoreChange() const;
//    int getTotalDamage() const;
//    bool hasRestartCondition() const;
//};