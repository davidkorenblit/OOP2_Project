//#include "CollisionManager.h"
//#include "LevelManager.h"
//#include <iostream>
//
//CollisionManager::CollisionManager() : m_levelManager(nullptr), m_needsPlayerReset(false) {
//}
//
//void CollisionManager::checkCollisions(const std::vector<GameObject*>& objects) {
//    for (size_t i = 0; i < objects.size(); ++i) {
//        for (size_t j = i + 1; j < objects.size(); ++j) {
//            GameObject* obj1 = objects[i];
//            GameObject* obj2 = objects[j];
//            if (obj1 && obj2 && areObjectsColliding(obj1, obj2)) {
//                if (obj1->isVehicle() || obj2->isVehicle()) {
//                    //std::cout << "💥 COLLISION: Vehicle collision detected" << std::endl;
//                }
//
//                auto result1 = obj1->acceptCollision(obj2);
//                if (result1 && result1->hasCollision()) {
//                    m_collisionHistory.push_back(std::move(result1));
//                    applyCollisionResult(*m_collisionHistory.back());
//                }
//
//                auto result2 = obj2->acceptCollision(obj1);
//                if (result2 && result2->hasCollision()) {
//                    m_collisionHistory.push_back(std::move(result2));
//                    applyCollisionResult(*m_collisionHistory.back());
//                }
//            }
//        }
//    }
//    processDelayedActions();
//}
//
//void CollisionManager::processDelayedActions() {
//    if (m_needsPlayerReset && m_levelManager) {
//        //std::cout << "DEBUG: Executing player reset!" << std::endl;
//        m_levelManager->resetPlayerVehicle();
//        m_needsPlayerReset = false;
//        //clearHistory();
//    }
//}
//
//bool CollisionManager::areObjectsColliding(GameObject* obj1, GameObject* obj2) {
//    if (!obj1 || !obj2) return false;
//
//    sf::FloatRect bounds1 = obj1->getBounds();
//    sf::FloatRect bounds2 = obj2->getBounds();
//    bool intersects = bounds1.intersects(bounds2);
//
//    if ((obj1->isVehicle() && obj2->isParkingSpot()) ||
//        (obj1->isParkingSpot() && obj2->isVehicle())) {
//
//        const float EXPAND = 20.0f;
//        bounds1.left -= EXPAND;
//        bounds1.top -= EXPAND;
//        bounds1.width += 2 * EXPAND;
//        bounds1.height += 2 * EXPAND;
//
//        intersects = bounds1.intersects(bounds2);
//    }
//
//    return intersects;
//}
//
//void CollisionManager::applyCollisionResult(const CollisionResult& result) {
//    if (result.shouldRestartLevel()) {
//        std::cout << "DEBUG: Setting player reset flag!" << std::endl;
//        m_needsPlayerReset = true;
//    }
//
//    if (result.getType() == CollisionType::GOAL_REACHED) {
//        std::cout << "VICTORY! Setting game won flag!" << std::endl;
//        m_gameWon = true;
//    }
//}
//
//int CollisionManager::getTotalScoreChange() const {
//    int total = 0;
//    for (const auto& result : m_collisionHistory) {
//        total += result->getScoreChange();
//    }
//    return total;
//}
//
//int CollisionManager::getTotalDamage() const {
//    int total = 0;
//    for (const auto& result : m_collisionHistory) {
//        total += result->getDamage();
//    }
//    return total;
//}
//
//bool CollisionManager::hasRestartCondition() const {
//    for (const auto& result : m_collisionHistory) {
//        if (result->shouldRestartLevel()) {
//            return true;
//        }
//    }
//    return false;
//}