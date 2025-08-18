#pragma once
#include <stdexcept>
#include <string>

class GameException : public std::exception {
private:
    std::string m_message;
    std::string m_context;

public:
    explicit GameException(const std::string& message, const std::string& context = "");
    virtual ~GameException() noexcept = default;

    const char* what() const noexcept override;
    const std::string& getContext() const noexcept;
    virtual std::string getFullMessage() const;
};

class ResourceNotFoundException : public GameException {
public:
    explicit ResourceNotFoundException(const std::string& resourceName, const std::string& path = "");
    std::string getFullMessage() const override;
};

class InvalidLevelException : public GameException {
private:
    std::string m_levelName;

public:
    explicit InvalidLevelException(const std::string& levelName, const std::string& reason = "");
    std::string getFullMessage() const override;
    const std::string& getLevelName() const noexcept;
};

class CollisionDetectionException : public GameException {
public:
    explicit CollisionDetectionException(const std::string& message, const std::string& context = "CollisionDetector");
    std::string getFullMessage() const override;
};

class GameStateException : public GameException {
private:
    std::string m_stateName;

public:
    explicit GameStateException(const std::string& stateName, const std::string& message, const std::string& context = "GameStateManager");
    std::string getFullMessage() const override;
    const std::string& getStateName() const noexcept;
};

class EffectProcessingException : public GameException {
public:
    explicit EffectProcessingException(const std::string& message, const std::string& context = "EffectManager");
    std::string getFullMessage() const override;
};

class ManagerInitializationException : public GameException {
private:
    std::string m_managerName;

public:
    explicit ManagerInitializationException(const std::string& managerName, const std::string& reason = "");
    std::string getFullMessage() const override;
    const std::string& getManagerName() const noexcept;
};

class LevelOperationException : public GameException {
private:
    std::string m_operation;

public:
    explicit LevelOperationException(const std::string& operation, const std::string& reason = "");
    std::string getFullMessage() const override;
    const std::string& getOperation() const noexcept;
};

class ObjectCreationException : public GameException {
private:
    std::string m_objectType;

public:
    explicit ObjectCreationException(const std::string& objectType, const std::string& reason = "");
    std::string getFullMessage() const override;
    const std::string& getObjectType() const noexcept;
};