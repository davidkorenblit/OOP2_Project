#pragma once
#include <SFML/System.hpp>
#include <string>

class ScoreTimeManager {
private:
    int m_currentScore;
    int m_currentLevel;
    sf::Clock m_levelClock;
    float m_levelTimeLimit;
    float m_timeRemaining;
    bool m_levelActive;

    int m_baseScorePerLevel;
    int m_timeBonus;

public:
    ScoreTimeManager();

    void startLevel(int levelNumber, float timeLimit = 300.0f);
    void completeLevel();
    void resetLevel();
    void update();

    void addScore(int points);
    void resetScore();

    int getCurrentScore() const { return m_currentScore; }
    int getCurrentLevel() const { return m_currentLevel; }
    float getTimeRemaining() const { return m_timeRemaining; }
    std::string getTimeRemainingString() const;

    bool isTimeUp() const { return m_timeRemaining <= 0.0f && m_levelActive; }
    bool isLevelActive() const { return m_levelActive; }

    std::string getScoreString() const;
    std::string getLevelString() const;
    std::string getUIString() const;
};