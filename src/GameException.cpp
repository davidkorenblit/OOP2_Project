#include "GameException.h"

GameException::GameException(const std::string& message, const std::string& context)
    : m_message(message), m_context(context) {
}

const char* GameException::what() const noexcept {
    return m_message.c_str();
}

const std::string& GameException::getContext() const noexcept {
    return m_context;
}

std::string GameException::getFullMessage() const {
    if (m_context.empty()) {
        return m_message;
    }
    return m_context + ": " + m_message;
}

ResourceNotFoundException::ResourceNotFoundException(const std::string& resourceName, const std::string& path)
    : GameException("Resource not found: " + resourceName, path.empty() ? "ResourceManager" : path) {
}

std::string ResourceNotFoundException::getFullMessage() const {
    return "Failed to load resource - " + GameException::getFullMessage();
}

InvalidLevelException::InvalidLevelException(const std::string& levelName, const std::string& reason)
    : GameException(reason.empty() ? "Invalid or corrupted level data" : reason, "LevelLoader")
    , m_levelName(levelName) {
}

std::string InvalidLevelException::getFullMessage() const {
    return "Level '" + m_levelName + "' - " + GameException::getFullMessage();
}

const std::string& InvalidLevelException::getLevelName() const noexcept {
    return m_levelName;
}

CollisionDetectionException::CollisionDetectionException(const std::string& message, const std::string& context)
    : GameException(message, context) {
}

std::string CollisionDetectionException::getFullMessage() const {
    return "Collision Detection Error - " + GameException::getFullMessage();
}

GameStateException::GameStateException(const std::string& stateName, const std::string& message, const std::string& context)
    : GameException(message, context), m_stateName(stateName) {
}

std::string GameStateException::getFullMessage() const {
    return "Game State '" + m_stateName + "' - " + GameException::getFullMessage();
}

const std::string& GameStateException::getStateName() const noexcept {
    return m_stateName;
}

EffectProcessingException::EffectProcessingException(const std::string& message, const std::string& context)
    : GameException(message, context) {
}

std::string EffectProcessingException::getFullMessage() const {
    return "Effect Processing Error - " + GameException::getFullMessage();
}

ManagerInitializationException::ManagerInitializationException(const std::string& managerName, const std::string& reason)
    : GameException(reason.empty() ? "Failed to initialize manager" : reason, "GameManager")
    , m_managerName(managerName) {
}

std::string ManagerInitializationException::getFullMessage() const {
    return "Manager '" + m_managerName + "' - " + GameException::getFullMessage();
}

const std::string& ManagerInitializationException::getManagerName() const noexcept {
    return m_managerName;
}

LevelOperationException::LevelOperationException(const std::string& operation, const std::string& reason)
    : GameException(reason.empty() ? "Level operation failed" : reason, "LevelManager")
    , m_operation(operation) {
}

std::string LevelOperationException::getFullMessage() const {
    return "Level Operation '" + m_operation + "' - " + GameException::getFullMessage();
}

const std::string& LevelOperationException::getOperation() const noexcept {
    return m_operation;
}

ObjectCreationException::ObjectCreationException(const std::string& objectType, const std::string& reason)
    : GameException(reason.empty() ? "Failed to create object" : reason, "ObjectFactory")
    , m_objectType(objectType) {
}

std::string ObjectCreationException::getFullMessage() const {
    return "Object Creation '" + m_objectType + "' - " + GameException::getFullMessage();
}

const std::string& ObjectCreationException::getObjectType() const noexcept {
    return m_objectType;
}