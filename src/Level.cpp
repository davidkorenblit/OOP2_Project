#include "Level.h"

Level::Level(const std::string& name, const std::string& backgroundTexture, const PlayerSpawn& playerSpawn)
    : m_name(name)
    , m_backgroundTexture(backgroundTexture)
    , m_playerSpawn(playerSpawn)
{
}

void Level::addObject(std::unique_ptr<GameObject> obj) {
    if (obj) {
        m_objects.push_back(std::move(obj));
    }
}

std::vector<GameObject*> Level::getAllObjectPointers() const {
    std::vector<GameObject*> result;
    result.reserve(m_objects.size());

    for (const auto& obj : m_objects) {
        if (obj) {
            result.push_back(obj.get());
        }
    }

    return result;
}

void Level::clearObjects() {
    m_objects.clear();
}
//new
void Level::addBoundary(const sf::FloatRect& boundary) {
    m_boundaries.push_back(boundary);
}

const std::vector<sf::FloatRect>& Level::getBoundaries() const {
    return m_boundaries;
}