#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "CollisionResult.h"

class CollisionDetector {
private:
    bool areObjectsColliding(GameObject* obj1, GameObject* obj2);
    //bool checkBoundaryCollisions(GameObject* player, const std::vector<sf::FloatRect>& boundaries);

public:
    CollisionDetector();
    ~CollisionDetector() = default;
   

    //new
    std::unique_ptr<CollisionResult> checkPlayerBoundaryCollision(GameObject* player,
        const std::vector<sf::FloatRect>& boundaries);
    // bool checkBoundaryCollisions(GameObject* player, const std::vector<sf::FloatRect>& boundaries);
    std::vector<std::unique_ptr<CollisionResult>> detectCollisions(const std::vector<GameObject*>& objects);
};