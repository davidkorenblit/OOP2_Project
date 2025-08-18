#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

class SoundManager {
private:
    static std::unique_ptr<SoundManager> s_instance;
    std::map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::map<std::string, sf::Sound> m_sounds;
    sf::Music m_backgroundMusic;
    float m_masterVolume;
    bool m_isMuted;

    void validateAndThrowLoadError(bool loadSuccess, const std::string& soundId, const std::string& filename);
    void configureSoundSettings(const std::string& soundId);
    float clampVolume(float volume);
    std::string m_currentBackgroundSound;
    std::map<std::string, bool> m_isPlaying;
    sf::Clock m_updateClock;

    SoundManager();

public:
    static SoundManager& getInstance();
    static void shutdown();

    void loadSound(const std::string& soundId, const std::string& filename);
    void loadMusic(const std::string& filename);
    void playSound(const std::string& soundId);
    void stopSound(const std::string& soundId);
    void stopAllSounds();

    void playBackgroundLoop(const std::string& soundId);
    void switchBackgroundLoop(const std::string& newSoundId);
    void stopAllBackgroundSounds();
    bool isCurrentlyPlaying(const std::string& soundId) const;
    void update();

    void playBackgroundMusic(bool loop = true);
    void stopBackgroundMusic();
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();

    void setMasterVolume(float volume);
    void setSoundVolume(const std::string& soundId, float volume);
    void setMusicVolume(float volume);

    void setMuted(bool muted);
    bool isMuted() const { return m_isMuted; }

    bool hasSound(const std::string& soundId) const;
    void unloadSound(const std::string& soundId);
    void unloadAllSounds();
    void loadAllGameSounds();

    size_t getLoadedSoundsCount() const { return m_soundBuffers.size(); }
};