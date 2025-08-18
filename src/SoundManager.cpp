#include "SoundManager.h"
#include "GameException.h"
#include <iostream>

std::unique_ptr<SoundManager> SoundManager::s_instance = nullptr;

SoundManager::SoundManager() : m_masterVolume(100.0f), m_isMuted(false) {
}

SoundManager& SoundManager::getInstance() {
    if (!s_instance) {
        s_instance = std::unique_ptr<SoundManager>(new SoundManager());
    }
    return *s_instance;
}

void SoundManager::shutdown() {
    if (s_instance) {
        s_instance->stopBackgroundMusic();
        s_instance->stopAllSounds();
        s_instance->unloadAllSounds();
        s_instance.reset();
    }
}

void SoundManager::validateAndThrowLoadError(bool loadSuccess, const std::string& soundId, const std::string& filename) {
    if (!loadSuccess) {
        throw ResourceNotFoundException(soundId, filename);
    }
}

void SoundManager::configureSoundSettings(const std::string& soundId) {
    m_sounds[soundId].setBuffer(m_soundBuffers[soundId]);
    m_sounds[soundId].setVolume(m_masterVolume);
    m_isPlaying[soundId] = false;
}

float SoundManager::clampVolume(float volume) {
    return std::max(0.0f, std::min(100.0f, volume));
}

void SoundManager::loadSound(const std::string& soundId, const std::string& filename) {
    if (hasSound(soundId)) {
        return;
    }

    sf::SoundBuffer buffer;
    validateAndThrowLoadError(buffer.loadFromFile(filename), soundId, filename);

    m_soundBuffers[soundId] = std::move(buffer);
    configureSoundSettings(soundId);
}

void SoundManager::loadMusic(const std::string& filename) {
    validateAndThrowLoadError(m_backgroundMusic.openFromFile(filename), "background_music", filename);
    m_backgroundMusic.setVolume(m_masterVolume * 0.7f);
}

void SoundManager::playSound(const std::string& soundId) {
    if (m_isMuted) return;

    auto it = m_sounds.find(soundId);
    if (it != m_sounds.end()) {
        it->second.play();
        m_isPlaying[soundId] = true;
    }
}

void SoundManager::playBackgroundLoop(const std::string& soundId) {
    if (m_isMuted) return;

    if (m_currentBackgroundSound == soundId && isCurrentlyPlaying(soundId)) {
        return;
    }

    if (!m_currentBackgroundSound.empty()) {
        stopSound(m_currentBackgroundSound);
    }

    auto it = m_sounds.find(soundId);
    if (it != m_sounds.end()) {
        if (soundId == "drive") {
            it->second.setVolume(m_masterVolume * 0.8f);
        }
        else {
            it->second.setVolume(m_masterVolume * 0.3f);
        }
        it->second.setLoop(true);
        it->second.play();
        m_currentBackgroundSound = soundId;
        m_isPlaying[soundId] = true;
    }
}

void SoundManager::switchBackgroundLoop(const std::string& newSoundId) {
    if (m_currentBackgroundSound != newSoundId) {
        playBackgroundLoop(newSoundId);
    }
}

bool SoundManager::isCurrentlyPlaying(const std::string& soundId) const {
    auto it = m_sounds.find(soundId);
    if (it != m_sounds.end()) {
        return it->second.getStatus() == sf::Sound::Playing;
    }
    return false;
}

void SoundManager::update() {
    for (auto& pair : m_isPlaying) {
        const std::string& soundId = pair.first;
        bool& wasPlaying = pair.second;

        bool isNowPlaying = isCurrentlyPlaying(soundId);

        if (wasPlaying && !isNowPlaying) {
            if (soundId == m_currentBackgroundSound) {
                m_currentBackgroundSound.clear();
            }
        }

        wasPlaying = isNowPlaying;
    }
}

void SoundManager::stopSound(const std::string& soundId) {
    auto it = m_sounds.find(soundId);
    if (it != m_sounds.end()) {
        it->second.stop();
        m_isPlaying[soundId] = false;

        if (soundId == m_currentBackgroundSound) {
            m_currentBackgroundSound.clear();
        }
    }
}

void SoundManager::stopAllBackgroundSounds() {
    if (!m_currentBackgroundSound.empty()) {
        auto it = m_sounds.find(m_currentBackgroundSound);
        if (it != m_sounds.end()) {
            it->second.stop();
            it->second.setLoop(false);
            m_isPlaying[m_currentBackgroundSound] = false;
        }
        m_currentBackgroundSound.clear();
    }
}

void SoundManager::stopAllSounds() {
    for (auto& sound : m_sounds) {
        sound.second.stop();
    }
    for (auto& playing : m_isPlaying) {
        playing.second = false;
    }
    m_currentBackgroundSound.clear();
}

void SoundManager::playBackgroundMusic(bool loop) {
    if (m_isMuted) return;

    m_backgroundMusic.setLoop(loop);
    m_backgroundMusic.play();
}

void SoundManager::stopBackgroundMusic() {
    m_backgroundMusic.stop();
}

void SoundManager::pauseBackgroundMusic() {
    m_backgroundMusic.pause();
}

void SoundManager::resumeBackgroundMusic() {
    if (!m_isMuted) {
        m_backgroundMusic.play();
    }
}

void SoundManager::setMasterVolume(float volume) {
    m_masterVolume = clampVolume(volume);

    for (auto& sound : m_sounds) {
        sound.second.setVolume(m_masterVolume);
    }
    m_backgroundMusic.setVolume(m_masterVolume * 0.7f);
}

void SoundManager::setSoundVolume(const std::string& soundId, float volume) {
    auto it = m_sounds.find(soundId);
    if (it != m_sounds.end()) {
        it->second.setVolume(clampVolume(volume));
    }
}

void SoundManager::setMusicVolume(float volume) {
    m_backgroundMusic.setVolume(clampVolume(volume));
}

void SoundManager::setMuted(bool muted) {
    m_isMuted = muted;

    if (muted) {
        stopAllSounds();
        pauseBackgroundMusic();
    }
    else {
        if (m_backgroundMusic.getStatus() == sf::Music::Paused) {
            resumeBackgroundMusic();
        }
    }
}

bool SoundManager::hasSound(const std::string& soundId) const {
    return m_soundBuffers.find(soundId) != m_soundBuffers.end();
}

void SoundManager::unloadSound(const std::string& soundId) {
    stopSound(soundId);
    m_sounds.erase(soundId);
    m_soundBuffers.erase(soundId);
    m_isPlaying.erase(soundId);
}

void SoundManager::unloadAllSounds() {
    stopAllSounds();
    m_sounds.clear();
    m_soundBuffers.clear();
    m_isPlaying.clear();
}

void SoundManager::loadAllGameSounds() {
    std::vector<std::pair<std::string, std::string>> soundConfigs = {
        {"game_start", "loop_sound.mp3"},
        {"crash", "crash_sound.mp3"},
        {"drive", "move_sound.mp3"},
        {"victory", "victory_sound.mp3"},
        {"moving_car", "m_car_sound.mp3"},
        {"gameover", "gameover_sound.mp3"}
    };

    for (const auto& config : soundConfigs) {
        try {
            loadSound(config.first, config.second);
        }
        catch (const ResourceNotFoundException& e) {
            std::cerr << "Warning: Could not load sound " << config.first
                << " from " << config.second << std::endl;
        }
    }

    try {
        loadMusic("loop_sound.mp3");
    }
    catch (const ResourceNotFoundException& e) {
        std::cerr << "Warning: Could not load background music" << std::endl;
    }
}