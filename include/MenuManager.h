#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <fstream>

enum class MenuOption {
    NONE,
    START_GAME,
    INSTRUCTIONS,
    EXIT
};

enum class MenuState {
    MAIN,
    INSTRUCTIONS
};

class MenuManager {
private:
    std::vector<std::unique_ptr<Button>> m_buttons;
    sf::RectangleShape m_background;
    sf::Font* m_font;
    MenuOption m_selectedOption;
    MenuState m_currentState;
    sf::Vector2f m_menuSize;
    sf::Vector2f m_menuPosition;

    sf::Text m_instructionsText;
    sf::RectangleShape m_instructionsBackground;
    std::string m_instructionsContent;

    void initializeMainMenu();
    void initializeInstructions();
    void loadInstructionsFromFile();
    void renderMainMenu(sf::RenderWindow& window);
    void renderInstructions(sf::RenderWindow& window);
    MenuOption handleMainMenuInput(const sf::Event& event);
    void handleInstructionsInput(const sf::Event& event);

public:
    MenuManager(sf::Font* font);
    void initializeMenu();
    MenuOption handleMenuInput(const sf::Event& event);
    void update(const sf::Vector2f& mousePos);
    void renderMenu(sf::RenderWindow& window);
    MenuOption getSelectedOption() const { return m_selectedOption; }
    void resetSelection() { m_selectedOption = MenuOption::NONE; }
    void returnToMainMenu() { m_currentState = MenuState::MAIN; }
};