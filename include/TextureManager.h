#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

class TextureManager {
private:
    static std::unique_ptr<TextureManager> s_instance;
    std::map<std::string, sf::Texture> m_textures;
private:
    void validateAndThrowLoadError(bool loadSuccess, const std::string& textureId, const std::string& source);
    void finalizeTextureLoading(const std::string& textureId, sf::Texture& texture);
    TextureManager() = default;

public:
    static TextureManager& getInstance();
    static void shutdown();

    void loadTexture(const std::string& textureId, const std::string& filename);
    void loadTextureWithTransparency(const std::string& textureId, const std::string& filename, const sf::Color& transparentColor = sf::Color::White);
    const sf::Texture& getTexture(const std::string& textureId);
    bool hasTexture(const std::string& textureId) const;
    void unloadTexture(const std::string& textureId);
    void unloadAllTextures();
    void loadAllGameTextures();

    size_t getLoadedTexturesCount() const { return m_textures.size(); }
};