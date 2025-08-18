#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, sf::Font* font)
    : m_font(font), m_state(ButtonState::NORMAL)
    , m_normalColor(sf::Color(70, 70, 70))
    , m_hoverColor(sf::Color(100, 100, 100))
    , m_clickColor(sf::Color(50, 50, 50))
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(m_normalColor);
    m_shape.setOutlineThickness(3.0f);
    m_shape.setOutlineColor(sf::Color(200, 200, 200));

    if (m_font) {
        m_text.setFont(*m_font);
        m_text.setString(text);
        m_text.setCharacterSize(26);
        m_text.setFillColor(sf::Color::White);
        m_text.setStyle(sf::Text::Bold);

        sf::FloatRect textBounds = m_text.getLocalBounds();
        sf::Vector2f textPos;
        textPos.x = position.x + (size.x - textBounds.width) / 2;
        textPos.y = position.y + (size.y - textBounds.height) / 2 - 5;
        m_text.setPosition(textPos);
    }
}

bool Button::isClicked(const sf::Vector2f& mousePos) const {
    return m_shape.getGlobalBounds().contains(mousePos);
}

bool Button::isHovered(const sf::Vector2f& mousePos) const {
    return m_shape.getGlobalBounds().contains(mousePos);
}

void Button::update(const sf::Vector2f& mousePos) {
    if (isHovered(mousePos)) {
        m_state = ButtonState::HOVERED;
        m_shape.setFillColor(m_hoverColor);
        m_shape.setOutlineColor(sf::Color::White);
        m_shape.setOutlineThickness(4.0f);
    }
    else {
        m_state = ButtonState::NORMAL;
        m_shape.setFillColor(m_normalColor);
        m_shape.setOutlineColor(sf::Color(200, 200, 200));
        m_shape.setOutlineThickness(3.0f);
    }
}

void Button::render(sf::RenderWindow& window) const {
    window.draw(m_shape);
    if (m_font) {
        window.draw(m_text);
    }
}

void Button::setText(const std::string& text) {
    if (m_font) {
        m_text.setString(text);
    }
}

void Button::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
    if (m_font) {
        sf::FloatRect textBounds = m_text.getLocalBounds();
        sf::Vector2f size = m_shape.getSize();
        sf::Vector2f textPos;
        textPos.x = position.x + (size.x - textBounds.width) / 2;
        textPos.y = position.y + (size.y - textBounds.height) / 2 - 5;
        m_text.setPosition(textPos);
    }
}

void Button::setColors(const sf::Color& normal, const sf::Color& hover, const sf::Color& click) {
    m_normalColor = normal;
    m_hoverColor = hover;
    m_clickColor = click;
    m_shape.setFillColor(m_normalColor);
}