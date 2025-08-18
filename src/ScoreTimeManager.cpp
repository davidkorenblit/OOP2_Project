#include "ScoreTimeManager.h"
#include <sstream>
#include <iomanip>

ScoreTimeManager::ScoreTimeManager()
    : m_currentScore(0), m_currentLevel(1), m_levelTimeLimit(300.0f),
    m_timeRemaining(300.0f), m_levelActive(false),
    m_baseScorePerLevel(1000), m_timeBonus(10) {
}

void ScoreTimeManager::startLevel(int levelNumber, float timeLimit) {
    m_currentLevel = levelNumber;
    m_levelTimeLimit = timeLimit;
    m_timeRemaining = timeLimit;
    m_levelActive = true;
    m_levelClock.restart();
}

void ScoreTimeManager::completeLevel() {
    if (!m_levelActive) return;

    m_levelActive = false;

    int levelScore = m_baseScorePerLevel;
    int timeScore = static_cast<int>(m_timeRemaining * m_timeBonus);

    addScore(levelScore + timeScore);
}

void ScoreTimeManager::resetLevel() {
    m_timeRemaining = m_levelTimeLimit;
    m_levelActive = true;
    m_levelClock.restart();
}

void ScoreTimeManager::update() {
    if (!m_levelActive) return;

    float elapsed = m_levelClock.getElapsedTime().asSeconds();
    m_timeRemaining = m_levelTimeLimit - elapsed;

    if (m_timeRemaining < 0.0f) {
        m_timeRemaining = 0.0f;
    }
}

void ScoreTimeManager::addScore(int points) {
    m_currentScore += points;
}

void ScoreTimeManager::resetScore() {
    m_currentScore = 0;
}

std::string ScoreTimeManager::getTimeRemainingString() const {
    int minutes = static_cast<int>(m_timeRemaining) / 60;
    int seconds = static_cast<int>(m_timeRemaining) % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes
        << ":" << std::setfill('0') << std::setw(2) << seconds;
    return oss.str();
}

std::string ScoreTimeManager::getScoreString() const {
    return "Score: " + std::to_string(m_currentScore);
}

std::string ScoreTimeManager::getLevelString() const {
    return "Level: " + std::to_string(m_currentLevel);
}

std::string ScoreTimeManager::getUIString() const {
    return getScoreString() + "    Time: " + getTimeRemainingString() + "    " + getLevelString();
}