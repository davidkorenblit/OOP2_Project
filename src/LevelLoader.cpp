#include "LevelLoader.h"
#include "ObjectFactory.h"
#include "GameException.h"

std::unique_ptr<Level> LevelLoader::loadFromFile(const std::string& filename, int levelIndex) {
    if (filename.empty()) {
        throw InvalidLevelException(filename, "Empty filename provided");
    }

    try {
           return ObjectFactory::createLevelFromJson(filename, levelIndex);

    }
    catch (const std::exception& e) {
        throw InvalidLevelException(filename, "Failed to load level: " + std::string(e.what()));
    }
}
