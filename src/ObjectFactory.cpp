#include "ObjectFactory.h"
#include "StaticObstacle.h"
#include "ParkedCar.h"
#include "MovingCar.h"
#include "ParkingSpot.h"
#include "GameException.h"
#include <iostream>
#include <fstream>
#include <sstream>

void ObjectFactory::initialize() {
    std::cout << "ObjectFactory initialized" << std::endl;
}

std::string ObjectFactory::readJsonFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw ObjectCreationException("JsonFile", "Failed to open JSON file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    if (content.empty()) {
        throw ObjectCreationException("JsonFile", "JSON file is empty: " + filename);
    }

    return content;
}

std::vector<ObjectFactory::DataMap> ObjectFactory::parseJsonFile(const std::string& filename) {
    std::string jsonContent = readJsonFile(filename);

    std::vector<DataMap> objects;
    std::istringstream stream(jsonContent);
    std::string line;
    DataMap currentObject;
    bool insideObject = false;

    while (std::getline(stream, line)) {
        line.erase(0, line.find_first_not_of(" \t\n\r"));
        line.erase(line.find_last_not_of(" \t\n\r,") + 1);

        if (line == "{") {
            insideObject = true;
            currentObject.clear();
        }
        else if (line == "}" || line == "},") {
            if (insideObject && !currentObject.empty()) {
                objects.push_back(currentObject);
                currentObject.clear();
            }
            insideObject = false;
        }
        else if (insideObject && line.find(":") != std::string::npos) {
            size_t colonPos = line.find(':');
            std::string key = extractQuotedString(line.substr(0, colonPos));
            std::string value = extractValue(line.substr(colonPos + 1));

            if (!key.empty() && !value.empty()) {
                currentObject[key] = value;
            }
        }
    }

    return objects;
}

std::unique_ptr<Level> ObjectFactory::createLevelFromJson(const std::string& filename, int levelIndex) {
    auto jsonData = parseJsonFile(filename);

    if (jsonData.empty()) {
        throw ObjectCreationException("Level", "No objects found in JSON data: " + filename);
    }

    PlayerSpawn spawn;
    spawn.position = sf::Vector2f(0, 0);
    spawn.angle = 90.0f;

    for (const auto& objectData : jsonData) {
        auto typeIt = objectData.find("type");
        if (typeIt == objectData.end()) continue;

        std::string type = typeIt->second;

        if (type == "player_spawn") {
            spawn = createPlayerSpawn(objectData);
        }
    }

    std::string levelName = "Level " + std::to_string(levelIndex);
    std::string bgTexture = "level_" + std::to_string(levelIndex - 1);

    auto level = std::make_unique<Level>(levelName, bgTexture, spawn);

    for (const auto& objectData : jsonData) {
        auto typeIt = objectData.find("type");
        if (typeIt == objectData.end()) continue;

        std::string type = typeIt->second;

        if (type == "player_spawn") {
            continue;
        }
        if (type == "border") {
            level->addBoundary(createBoundary(objectData));
            continue;
        }

        auto obj = createFromJsonData(type, objectData);
        if (obj) {
            level->addObject(std::move(obj));
        }
    }

    return level;
}

std::string ObjectFactory::extractQuotedString(const std::string& str) {
    std::string trimmed = str;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);

    if (trimmed.length() >= 2 && trimmed.front() == '"' && trimmed.back() == '"') {
        return trimmed.substr(1, trimmed.length() - 2);
    }
    return trimmed;
}

std::string ObjectFactory::extractValue(const std::string& str) {
    std::string trimmed = str;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r,") + 1);

    if (trimmed.length() >= 2 && trimmed.front() == '"' && trimmed.back() == '"') {
        return trimmed.substr(1, trimmed.length() - 2);
    }
    return trimmed;
}

sf::Vector2f ObjectFactory::extractPosition(const DataMap& data) {
    try {
        float x = extractFloat(data, "x");
        float y = extractFloat(data, "y");
        return sf::Vector2f(x, y);
    }
    catch (const std::exception& e) {
        throw ObjectCreationException("Position", "Failed to extract position: " + std::string(e.what()));
    }
}

sf::Vector2f ObjectFactory::extractDirection(const DataMap& data) {
    try {
        float dirX = extractFloat(data, "direction_x");
        if (dirX == 0.0f) dirX = extractFloat(data, "directionX");

        float dirY = extractFloat(data, "direction_y");
        if (dirY == 0.0f) dirY = extractFloat(data, "directionY");

        return sf::Vector2f(dirX, dirY);
    }
    catch (const std::exception& e) {
        throw ObjectCreationException("Direction", "Failed to extract direction: " + std::string(e.what()));
    }
}

std::string ObjectFactory::extractTexture(const DataMap& data, const std::string& defaultTexture) {
    auto it = data.find("texture");
    return (it != data.end()) ? it->second : defaultTexture;
}

float ObjectFactory::extractFloat(const DataMap& data, const std::string& key, float defaultValue) {
    auto it = data.find(key);
    if (it != data.end()) {
        try {
            return std::stof(it->second);
        }
        catch (const std::exception& e) {
            throw ObjectCreationException("FloatConversion", "Failed to convert " + key + " to float: " + it->second);
        }
    }
    return defaultValue;
}

template<typename T>
std::unique_ptr<GameObject> ObjectFactory::createBasicObject(const DataMap& data, const std::string& defaultTexture) {
    try {
        sf::Vector2f pos = extractPosition(data);
        std::string texture = extractTexture(data, defaultTexture);
        auto obj = std::make_unique<T>(pos, texture);

        sf::Vector2f direction = extractDirection(data);
        if (direction.x != 0.0f || direction.y != 0.0f) {
            float angleFromDirection = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f;
            obj->setRotation(angleFromDirection);
        }

        return obj;
    }
    catch (const std::exception& e) {
        throw ObjectCreationException("BasicObject", "Failed to create basic object: " + std::string(e.what()));
    }
}

template<typename T>
std::unique_ptr<GameObject> ObjectFactory::createMovingObject(const DataMap& data, float defaultSpeed, float defaultRespawn) {
    try {
        float startX = extractFloat(data, "start_x");
        if (startX == 0.0f) startX = extractFloat(data, "startX");
        if (startX == 0.0f) startX = extractFloat(data, "x");

        float startY = extractFloat(data, "start_y");
        if (startY == 0.0f) startY = extractFloat(data, "startY");
        if (startY == 0.0f) startY = extractFloat(data, "y");

        sf::Vector2f direction = extractDirection(data);
        if (direction.x == 0.0f && direction.y == 0.0f) {
            direction = sf::Vector2f(1.0f, 0.0f);
        }

        float speed = extractFloat(data, "speed", defaultSpeed);
        float respawn = extractFloat(data, "respawn_delay", defaultRespawn);
        if (respawn == 0.0f) respawn = extractFloat(data, "respawnDelay", defaultRespawn);

        return std::make_unique<T>(sf::Vector2f(startX, startY), direction, speed, respawn);
    }
    catch (const std::exception& e) {
        throw ObjectCreationException("MovingObject", "Failed to create moving object: " + std::string(e.what()));
    }
}

std::unique_ptr<GameObject> ObjectFactory::createParkedCarWithRandomTexture(const DataMap& data) {
    try {
        sf::Vector2f pos = extractPosition(data);

        std::vector<std::string> carTextures = { "parked_car_red", "parked_car_blue", "parked_car_green" };
        int index = static_cast<int>(pos.x + pos.y) % carTextures.size();
        std::string texture = carTextures[index];

        return std::make_unique<ParkedCar>(pos, texture);
    }
    catch (const std::exception& e) {
        throw ObjectCreationException("ParkedCar", "Failed to create parked car: " + std::string(e.what()));
    }
}

sf::FloatRect ObjectFactory::createBoundary(const DataMap& jsonData) {
    float x = extractFloat(jsonData, "x", 0.0f);
    float y = extractFloat(jsonData, "y", 0.0f);
    float width = extractFloat(jsonData, "width", 1.0f);
    float height = extractFloat(jsonData, "height", 1.0f);
    return sf::FloatRect(x, y, width, height);
}

PlayerSpawn ObjectFactory::createPlayerSpawn(const DataMap& jsonData) {
    PlayerSpawn spawn;
    spawn.position.x = extractFloat(jsonData, "x", 670.0f);
    spawn.position.y = extractFloat(jsonData, "y", 210.0f);
    spawn.angle = extractFloat(jsonData, "angle", 90.0f);
    spawn.direction = extractDirection(jsonData);
    return spawn;
}

std::unique_ptr<GameObject> ObjectFactory::create(const std::string& type, float x, float y, const std::string& texture) {
    if (type.empty()) {
        throw ObjectCreationException(type, "Empty object type provided");
    }

    try {
        DataMap data;
        data["x"] = std::to_string(x);
        data["y"] = std::to_string(y);
        if (!texture.empty()) {
            data["texture"] = texture;
        }
        return createFromJsonData(type, data);
    }
    catch (const GameException& e) {
        throw;
    }
    catch (const std::exception& e) {
        throw ObjectCreationException(type, "Failed to create object: " + std::string(e.what()));
    }
}

std::unique_ptr<GameObject> ObjectFactory::createMoving(const std::string& type, float startX, float startY,
    float dirX, float dirY, float speed, float respawnDelay, const std::string& texture) {

    if (type.empty()) {
        throw ObjectCreationException(type, "Empty moving object type provided");
    }

    try {
        DataMap data;
        data["startX"] = std::to_string(startX);
        data["startY"] = std::to_string(startY);
        data["directionX"] = std::to_string(dirX);
        data["directionY"] = std::to_string(dirY);
        data["speed"] = std::to_string(speed);
        data["respawnDelay"] = std::to_string(respawnDelay);
        if (!texture.empty()) {
            data["texture"] = texture;
        }
        return createFromJsonData(type, data);
    }
    catch (const GameException& e) {
        throw;
    }
    catch (const std::exception& e) {
        throw ObjectCreationException(type, "Failed to create moving object: " + std::string(e.what()));
    }
}

std::unique_ptr<GameObject> ObjectFactory::createFromJsonData(const std::string& type, const DataMap& jsonData) {
    if (type.empty()) {
        throw ObjectCreationException(type, "Empty object type in JSON data");
    }

    if (jsonData.empty()) {
        throw ObjectCreationException(type, "Empty JSON data provided");
    }

    try {
        std::unique_ptr<GameObject> obj = nullptr;

        if (type == "StaticObstacle" || type == "obstacle") {
            obj = createBasicObject<StaticObstacle>(jsonData, "traffic_cone");
        }
        else if (type == "ParkedCar" || type == "parkingcar") {
            obj = createBasicObject<ParkedCar>(jsonData, "parked_car_red");
        }
        else if (type == "parking_spot") {
            obj = createBasicObject<ParkingSpot>(jsonData, "parking_spot");
        }
        else if (type == "MovingCar" || type == "movingcar") {
            obj = createMovingObject<MovingCar>(jsonData, 80.0f, 3.0f);
        }
        else {
            throw ObjectCreationException(type, "Unknown object type: " + type);
        }

        if (obj) {
            float angle = extractFloat(jsonData, "angle", 0.0f);
            if (angle != 0.0f) {
                obj->setRotation(angle);
            }
        }

        return obj;
    }
    catch (const GameException& e) {
        throw;
    }
    catch (const std::exception& e) {
        throw ObjectCreationException(type, "Failed to create object from JSON: " + std::string(e.what()));
    }
}