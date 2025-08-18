#include "CollisionDetector.h"
#include "GameException.h"
#include <iostream>

CollisionDetector::CollisionDetector() {
}

std::vector<std::unique_ptr<CollisionResult>> CollisionDetector::detectCollisions(const std::vector<GameObject*>& objects) {
    if (objects.empty()) {
        throw CollisionDetectionException("Empty objects list provided for collision detection");
    }


    std::vector<std::unique_ptr<CollisionResult>> results;

    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            GameObject* obj1 = objects[i];
            GameObject* obj2 = objects[j];

            if (!obj1 || !obj2) {
                throw CollisionDetectionException("Null object found in collision detection at indices " +
                    std::to_string(i) + " and " + std::to_string(j));
            }

            if (obj1->isColliding(*obj2)) {
                //if (areObjectsColliding(obj1, obj2)) {
                if (obj1->isVehicle() || obj2->isVehicle()) {
                    //std::cout << "💥 COLLISION: Vehicle collision detected" << std::endl;
                }

                auto result1 = obj1->acceptCollision(obj2);
                if (!result1) {
                    throw CollisionDetectionException("Failed to get collision result from object with another object");
                }
                if (result1->hasCollision()) {
                    results.push_back(std::move(result1));
                }

                auto result2 = obj2->acceptCollision(obj1);
                if (!result2) {
                    throw CollisionDetectionException("Failed to get collision result from object with another object");
                }
                if (result2->hasCollision()) {
                    results.push_back(std::move(result2));
                }
            }
        }
    }

    return results;
}

bool CollisionDetector::areObjectsColliding(GameObject* obj1, GameObject* obj2) {
    if (!obj1 || !obj2) {
        throw CollisionDetectionException("Cannot check collision with null objects");
    }

    sf::FloatRect bounds1 = obj1->getBounds();
    sf::FloatRect bounds2 = obj2->getBounds();

    if ((obj1->isVehicle() && obj2->isParkingSpot()) ||
        (obj1->isParkingSpot() && obj2->isVehicle())) {

        const float EXPAND = 8.0f;
        bounds1.left -= EXPAND;
        bounds1.top -= EXPAND;
        bounds1.width += 2 * EXPAND;
        bounds1.height += 2 * EXPAND;

        return bounds1.intersects(bounds2);
    }

    if (obj1->isVehicle() || obj2->isVehicle()) {
        const float EXPAND = 8.0f;

        bounds1.left -= EXPAND;
        bounds1.top -= EXPAND;
        bounds1.width += 2 * EXPAND;
        bounds1.height += 2 * EXPAND;

        bounds2.left -= EXPAND;
        bounds2.top -= EXPAND;
        bounds2.width += 2 * EXPAND;
        bounds2.height += 2 * EXPAND;

        return bounds1.intersects(bounds2);
    }

    return bounds1.intersects(bounds2);
}


std::unique_ptr<CollisionResult> CollisionDetector::checkPlayerBoundaryCollision(GameObject* player,
    const std::vector<sf::FloatRect>& boundaries) {
    if (!player) {
        return CollisionResult::createNoCollision();
    }

    sf::FloatRect playerBounds = player->getBounds();
    for (const auto& boundary : boundaries) {
        if (playerBounds.intersects(boundary)) {
            return std::make_unique<CollisionResult>(
                CollisionType::TRAFFIC_VIOLATION,
                -50,
                0,
                true,
                EffectType::NONE,
                "Hit boundary - returning to start"
            );
        }
    }
    return CollisionResult::createNoCollision();
}