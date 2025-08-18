#include "GameManager.h"
#include "GameException.h"
#include <iostream>

int main() {
    try {
        GameManager gameManager;
        gameManager.initialize();
        gameManager.run();
        return 0;
    }
    catch (const GameException& e) {
        std::cerr << "Game error: " << e.getFullMessage() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}