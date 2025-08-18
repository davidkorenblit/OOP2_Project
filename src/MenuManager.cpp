#include "MenuManager.h"
#include "Constants.h"

MenuManager::MenuManager(sf::Font* font)
    : m_font(font), m_selectedOption(MenuOption::NONE), m_currentState(MenuState::MAIN) {
    m_menuSize = sf::Vector2f(500.0f, 400.0f);
    m_menuPosition = sf::Vector2f((Constants::WINDOW_WIDTH - m_menuSize.x) / 2,
        (Constants::WINDOW_HEIGHT - m_menuSize.y) / 2);
}

void MenuManager::initializeMenu() {
    initializeMainMenu();
    loadInstructionsFromFile();
    initializeInstructions();
}

void MenuManager::initializeMainMenu() {
    m_background.setSize(m_menuSize);
    m_background.setPosition(m_menuPosition);
    m_background.setFillColor(sf::Color(25, 35, 50, 200));
    m_background.setOutlineThickness(4.0f);
    m_background.setOutlineColor(sf::Color(100, 150, 255, 255));

    sf::Vector2f buttonSize(280.0f, 65.0f);
    float centerX = m_menuPosition.x + (m_menuSize.x - buttonSize.x) / 2;
    float startY = m_menuPosition.y + 90.0f;

    m_buttons.clear();

    auto startButton = std::make_unique<Button>(sf::Vector2f(centerX, startY), buttonSize, "Start Game", m_font);
    startButton->setColors(sf::Color(50, 150, 50), sf::Color(70, 200, 70), sf::Color(30, 120, 30));
    m_buttons.push_back(std::move(startButton));

    auto instructionsButton = std::make_unique<Button>(sf::Vector2f(centerX, startY + 85), buttonSize, "Instructions", m_font);
    instructionsButton->setColors(sf::Color(50, 100, 200), sf::Color(70, 130, 255), sf::Color(30, 80, 150));
    m_buttons.push_back(std::move(instructionsButton));

    auto exitButton = std::make_unique<Button>(sf::Vector2f(centerX, startY + 170), buttonSize, "Exit", m_font);
    exitButton->setColors(sf::Color(200, 50, 50), sf::Color(255, 70, 70), sf::Color(150, 30, 30));
    m_buttons.push_back(std::move(exitButton));
}

void MenuManager::loadInstructionsFromFile() {
    std::ifstream file("instructions.txt");
    if (file.is_open()) {
        std::string line;
        m_instructionsContent.clear();
        while (std::getline(file, line)) {
            m_instructionsContent += line + "\n";
        }
        file.close();
    }
    else {
        m_instructionsContent = "GAME INSTRUCTIONS\n\n";
        m_instructionsContent += "OBJECTIVE:\n";
        m_instructionsContent += "Park your car in the designated parking spot\n";
        m_instructionsContent += "without hitting obstacles or other cars.\n\n";
        m_instructionsContent += "CONTROLS:\n";
        m_instructionsContent += "W - Move Forward\n";
        m_instructionsContent += "A - Turn Left\n";
        m_instructionsContent += "S - Move Backward\n";
        m_instructionsContent += "D - Turn Right\n";
        m_instructionsContent += "H - Horn Sound\n";
        m_instructionsContent += "P - Pause Game\n";
        m_instructionsContent += "R - Restart Level\n";
        m_instructionsContent += "ESC - Menu\n\n";
        m_instructionsContent += "TIPS:\n";
        m_instructionsContent += "- Drive carefully to avoid collisions\n";
        m_instructionsContent += "- Use reverse to maneuver in tight spaces\n\n";
        m_instructionsContent += "Press any key to return to menu";
    }
}

void MenuManager::initializeInstructions() {
    if (!m_font) return;

    sf::Vector2f instructionsSize(700.0f, 550.0f);
    sf::Vector2f instructionsPos((Constants::WINDOW_WIDTH - instructionsSize.x) / 2,
        (Constants::WINDOW_HEIGHT - instructionsSize.y) / 2);

    m_instructionsBackground.setSize(instructionsSize);
    m_instructionsBackground.setPosition(instructionsPos);
    m_instructionsBackground.setFillColor(sf::Color(20, 30, 45, 230));
    m_instructionsBackground.setOutlineThickness(4.0f);
    m_instructionsBackground.setOutlineColor(sf::Color(100, 150, 255));

    m_instructionsText.setFont(*m_font);
    m_instructionsText.setString(m_instructionsContent);
    m_instructionsText.setCharacterSize(18);
    m_instructionsText.setFillColor(sf::Color::White);
    m_instructionsText.setPosition(instructionsPos.x + 40, instructionsPos.y + 40);
}

MenuOption MenuManager::handleMenuInput(const sf::Event& event) {
    if (m_currentState == MenuState::MAIN) {
        return handleMainMenuInput(event);
    }
    else if (m_currentState == MenuState::INSTRUCTIONS) {
        handleInstructionsInput(event);
        return MenuOption::NONE;
    }
    return MenuOption::NONE;
}

MenuOption MenuManager::handleMainMenuInput(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (m_buttons[0]->isClicked(mousePos)) {
            m_selectedOption = MenuOption::START_GAME;
            return m_selectedOption;
        }
        if (m_buttons[1]->isClicked(mousePos)) {
            m_currentState = MenuState::INSTRUCTIONS;
            return MenuOption::NONE;
        }
        if (m_buttons[2]->isClicked(mousePos)) {
            m_selectedOption = MenuOption::EXIT;
            return m_selectedOption;
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        m_selectedOption = MenuOption::START_GAME;
        return m_selectedOption;
    }

    return MenuOption::NONE;
}

void MenuManager::handleInstructionsInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        m_currentState = MenuState::MAIN;
    }
}

void MenuManager::update(const sf::Vector2f& mousePos) {
    if (m_currentState == MenuState::MAIN) {
        for (auto& button : m_buttons) {
            button->update(mousePos);
        }
    }
}

void MenuManager::renderMenu(sf::RenderWindow& window) {
    if (m_currentState == MenuState::MAIN) {
        renderMainMenu(window);
    }
    else if (m_currentState == MenuState::INSTRUCTIONS) {
        renderInstructions(window);
    }
}

void MenuManager::renderMainMenu(sf::RenderWindow& window) {
    window.draw(m_background);
    for (const auto& button : m_buttons) {
        button->render(window);
    }
}

void MenuManager::renderInstructions(sf::RenderWindow& window) {
    window.draw(m_instructionsBackground);
    window.draw(m_instructionsText);
}