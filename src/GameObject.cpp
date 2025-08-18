#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>

int GameObject::s_nextId = 1;

GameObject::GameObject(const sf::Vector2f& size, const std::string& textureId)
    : m_size(size)
    , m_id(s_nextId++)
{
    if (!textureId.empty()) {
        setTextureFromManager(textureId);
    }
}

bool GameObject::isColliding(const GameObject& other) const {
    return getBounds().intersects(other.getBounds());
}

void GameObject::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite, sf::RenderStates::Default);
}

void GameObject::setScale(float scale) {
    m_sprite.setScale(scale, scale);
}

void GameObject::setTextureFromManager(const std::string& textureId) {
    const sf::Texture& texture = TextureManager::getInstance().getTexture(textureId);
    m_sprite.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();
    m_sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    m_sprite.setScale(1.0f, 1.0f);
}

sf::FloatRect GameObject::getBounds() const
{
    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    return bounds;

}
