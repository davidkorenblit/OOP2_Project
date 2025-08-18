#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace Constants {

    constexpr int FPS = 60;
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 608;
    const sf::Vector2u WINDOW_SIZE(WINDOW_WIDTH, WINDOW_HEIGHT);
    const std::string WINDOW_TITLE = "Parking 2D - C++ Edition";

    namespace Assets {
        const std::string BASIC_CAR = "basic-car.png";
        const std::string F1_CAR = "f1-car.png";
        const std::string POLICE_CAR = "rpolice-car.png";
        const std::string SPORTS_CAR = "sports-car.png";
        const std::string YOU_WIN = "youwin.png";
        const std::string MENU = "menu_background.png";


        const std::string LEVEL1_BACKGROUND = "level_0.png";
        const std::string LEVEL2_BACKGROUND = "level_1.png";
        const std::string LEVEL3_BACKGROUND = "level_2.png";

        const std::string CAR_HORN = "car-horn.mp3";
        const std::string RETRO_FONT = "retroFont.ttf";
    }

    namespace Physics {
        constexpr float START_X = 10.0f;
        constexpr float START_Y = 10.0f;
        constexpr float PIXEL_ALIGNMENT = 32.0f;
        constexpr float MAX_STEERING_ANGLE = 120.0f;
        constexpr float MAX_ACCELERATION = 300.0f;
        constexpr float MAX_VELOCITY = 200.0f;
        constexpr float DECELERATION = 2.0f;
        constexpr float REVERSE_ACCELERATION = 40.0f;
        constexpr float VEHICLE_LENGTH = 4.0f;
        constexpr float STEERING_RATE = 150.0f;

        constexpr float PLAYER_WIDTH = 50.0f;
        constexpr float PLAYER_HEIGHT = 100.0f;
        constexpr float PLAYER_INIT_ROTATION = 180.0f;

        constexpr float PIXELS_PER_METER = 32.0f;
        constexpr float MOVEMENT_THRESHOLD = 1.0f;
        constexpr float LINEAR_DAMPING = 0.8f;
        constexpr float ANGULAR_DAMPING = 1.5f;
    }

    namespace Map {
        constexpr int BLOCK_SIZE = 16;
        const std::string GOAL_TILE = "brown.png";
        constexpr int GOAL_L1_WIDTH = 6;
        constexpr int GOAL_L1_HEIGHT = 12;
        constexpr int LEVEL1_REWARD = 100;
    }

    namespace Colors {
        const sf::Color GOLD(255, 185, 15);
        const sf::Color RED(255, 0, 0);
        const sf::Color BLACK(0, 0, 0);
        const sf::Color WHITE(255, 255, 255);
        const sf::Color GREEN(0, 255, 0);
        const sf::Color BOUNDARY_FILL(100, 100, 100, 150);
        const sf::Color BOUNDARY_OUTLINE(50, 50, 50);
    }

    namespace ObjectDefaults {
        constexpr float STATIC_OBSTACLE_SIZE = 16.0f;
        constexpr float ROAD_BOUNDARY_OUTLINE = 2.0f;
        constexpr float MOVING_CAR_SPEED = 120.0f;
        constexpr float MOVING_CAR_RESPAWN = 4.0f;
        constexpr float PEDESTRIAN_SPEED = 75.0f;
        constexpr float PEDESTRIAN_RESPAWN = 6.0f;
    }

    inline float tilesToPixels(float tileCoord) {
        return tileCoord * 32.0f;
    }

    inline sf::Vector2f getStartPosition() {
        return sf::Vector2f(tilesToPixels(Physics::START_X), tilesToPixels(Physics::START_Y));
    }
}