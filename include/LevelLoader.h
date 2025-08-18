#pragma once
#include "Level.h"
#include <memory>
#include <string>

class LevelLoader {
public:
    static std::unique_ptr<Level> loadFromFile(const std::string& filename, int levelIndex = 1);
};