#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class ButtonState {
    NORMAL,
    HOVERED,
    CLICKED
};

class Button {
private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Font* m_font;
    ButtonState m_state;
    sf::Color m_normalColor;
    sf::Color m_hoverColor;
    sf::Color m_clickColor;

public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, sf::Font* font);

    bool isClicked(const sf::Vector2f& mousePos) const;
    bool isHovered(const sf::Vector2f& mousePos) const;
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderWindow& window) const;

    void setText(const std::string& text);
    void setPosition(const sf::Vector2f& position);
    void setColors(const sf::Color& normal, const sf::Color& hover, const sf::Color& click);
};