#pragma once
#include <string>
#include <vector>
#include <memory>
#include "GameObject.h"

struct PlayerSpawn {
    sf::Vector2f position;
    float angle;
    sf::Vector2f direction;
};

class Level {
private:
    std::string m_name;
    std::string m_backgroundTexture;
    PlayerSpawn m_playerSpawn;
    std::vector<std::unique_ptr<GameObject>> m_objects;
    //new
    std::vector<sf::FloatRect> m_boundaries;

public:
    Level(const std::string& name, const std::string& backgroundTexture, const PlayerSpawn& playerSpawn);
    ~Level() = default;

    const std::string& getName() const { return m_name; }
    const std::string& getBackgroundTexture() const { return m_backgroundTexture; }
    const PlayerSpawn& getPlayerSpawn() const { return m_playerSpawn; }

    void addObject(std::unique_ptr<GameObject> obj);
    const std::vector<std::unique_ptr<GameObject>>& getAllObjects() const { return m_objects; }
    std::vector<GameObject*> getAllObjectPointers() const;

    size_t getObjectCount() const { return m_objects.size(); }
    void clearObjects();


    //new
    void addBoundary(const sf::FloatRect& boundary);
    const std::vector<sf::FloatRect>& getBoundaries() const;
};