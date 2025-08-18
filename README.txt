# Parking 2D Game - End of Semester B Project



## General Project Description
We were required to create a parking game, including textures, sounds, and multiple levels. The game allows the player to control a vehicle and park it in designated spots while avoiding collisions with static and dynamic obstacles. The game features realistic physics, time-based scoring, and progressive difficulty across multiple levels.

## System Architecture

### Core Game Managers

1. **GameManager**:
   - Main class managing overall game flow and state transitions
   - Responsible for main game loop, physics world management, and level progression
   - Coordinates between all sub-managers using event-driven communication
   - Handles game states: Menu, Playing, Paused, Game Over, You Win
   - **Merged with GameStateManager** for simplified state management

2. **LevelManager**:
   - Manages current level's complete lifecycle (objects, physics, collisions)
   - Controls player vehicle, collision detection, and effect processing
   - Uses callback pattern to communicate level events to GameManager
   - Responsible for level-specific logic while GameManager handles flow control

3. **ObjectFactory**:
   - **Centralized JSON parsing and object creation system**
   - Single source of truth for all level loading and object instantiation
   - Creates complete Level objects from JSON configuration files
   - Handles all game object types with template-based creation methods

4. **LevelLoader**:
   - **Simplified wrapper** around ObjectFactory functionality
   - Provides clean interface for level loading with exception handling
   - Minimal implementation after responsibility transfer to ObjectFactory

### Resource Managers

5. **SoundManager** (Singleton):
   - Manages all game audio including background music and sound effects
   - Supports looping background sounds and volume control
   - Tracks sound state and provides muting functionality

6. **TextureManager** (Singleton):
   - Handles texture loading with transparency support
   - Efficient resource caching and memory management
   - Provides both standard and transparent texture loading methods

### Specialized Managers

7. **CollisionDetector**:
   - Implements collision detection algorithms with object-specific logic
   - Handles boundary collision detection for level boundaries
   - Uses expanded bounding boxes for different object type combinations

8. **EffectManager**:
   - **Processes collision results and generates action recommendations**
   - Uses event pattern - recommends actions instead of executing them directly
   - GameManager receives recommendations and decides whether to execute

9. **ScoreTimeManager**:
   - Manages scoring system, time limits, and level progression tracking
   - Calculates time-based bonuses and handles game over conditions

10. **MenuManager**:
    - Handles main menu navigation and instructions display
    - Manages UI interaction and game initialization from menu

### Object Hierarchy

**GameObject (Abstract Base Class)**:
- Provides collision interface using Visitor pattern
- Handles rendering, positioning, and type identification
- Unique ID system for all game objects

**Vehicle Hierarchy**:
- **Vehicle** (Abstract): Box2D physics integration, movement control, and physics constraints
- **Car**: Player-controlled vehicle with input handling, health system, and collision responses

**Static Objects**:
- **StaticObstacle**: Traffic cones and barriers
- **ParkedCar**: Static vehicle obstacles that cause heavy damage
- **ParkingSpot**: Target areas for successful parking with containment checking

**Dynamic Objects**:
- **DynamicObstacle** (Base): Movement framework with respawn system
- **MovingCar**: AI-controlled moving obstacles with sound integration

**Utility Classes**:
- **CollisionResult**: Data container for collision outcomes with factory methods
- **Level**: Container for level data including objects, boundaries, and metadata
- **Button**: Interactive UI component with visual state management

## Architectural Improvements Made

### Responsibility Separation
- **Clear separation** between GameManager (game flow) and LevelManager (level content)
- **Event-driven communication** replacing tight coupling between managers
- **Single Source of Truth** for JSON parsing concentrated in ObjectFactory

### Code Quality Improvements
- **Reduced code duplication** in managers through helper function extraction
- **Eliminated unnecessary classes** (GameStateManager merged into GameManager)
- **Improved error handling** with centralized exception management

## File List

### Header Files (.h):
GameManager.h, LevelManager.h, Car.h, Vehicle.h, CollisionDetector.h, GameObject.h, EffectManager.h, MenuManager.h, ScoreTimeManager.h, TextureManager.h, SoundManager.h, LevelLoader.h, ObjectFactory.h, CollisionResult.h, Level.h, Constants.h, GameException.h, Button.h, StaticObstacle.h, DynamicObstacle.h, MovingCar.h, ParkedCar.h, ParkingSpot.h

### Implementation Files (.cpp):
main.cpp, GameManager.cpp, Car.cpp, CollisionDetector.cpp, LevelManager.cpp, GameObject.cpp, EffectManager.cpp, MenuManager.cpp, CollisionResult.cpp, Level.cpp, LevelLoader.cpp, Button.cpp, GameException.cpp, DynamicObstacle.cpp, MovingCar.cpp, ObjectFactory.cpp, ParkedCar.cpp, ParkingSpot.cpp, ScoreTimeManager.cpp, SoundManager.cpp, StaticObstacle.cpp, TextureManager.cpp, Vehicle.cpp

## Main Data Structures
- `std::vector<std::unique_ptr<GameObject>>` for game object management
- `std::map<std::string, sf::Texture>` for texture caching in TextureManager
- `std::map<std::string, sf::SoundBuffer>` for audio resource management
- `std::vector<sf::FloatRect>` for level boundary definitions
- `b2World` for Box2D physics simulation
- Smart pointers (`unique_ptr`) for safe memory management throughout the system
- `std::function<void(LevelEvent, const std::string&)>` for event callbacks

## Notable Algorithms and Patterns

### Design Patterns Implemented
- **Visitor Pattern**: GameObject collision system with `acceptCollision()` and `collideWith()` methods
- **Observer Pattern**: Event-driven communication between LevelManager and GameManager
- **Singleton Pattern**: TextureManager and SoundManager for global resource access
- **Factory Pattern**: ObjectFactory for centralized object creation from JSON data
- **State Pattern**: GameManager state machine and Button visual states
- **Template Method Pattern**: Vehicle hierarchy with shared physics and specialized behavior
- **Strategy Pattern**: Different collision responses based on object types

### Key Algorithms
- **AABB collision detection** with object-type-specific expanded bounds
- **Box2D physics integration** for realistic vehicle movement and constraints
- **Custom JSON parser** for level loading without external dependencies
- **Resource management** with automatic cleanup and caching
- **Time-based scoring** algorithm with performance bonuses
- **Event-driven architecture** for loose coupling between system components

## Exception Handling System
Custom exception hierarchy with context information:
- `GameException` (base class)
- `ResourceNotFoundException` for missing assets
- `InvalidLevelException` for corrupted level data
- `CollisionDetectionException` for collision system errors
- `LevelOperationException` for level management errors

## Memory Management
- Extensive use of smart pointers (`std::unique_ptr`) for automatic memory management
- RAII principles applied throughout the codebase
- Proper resource cleanup in manager destructors
- Exception-safe resource handling

## Known Issues
None currently identified.

## Additional Notes
The project demonstrates solid software engineering principles with clear separation of concerns, event-driven architecture, and comprehensive error handling. The codebase has been refactored to eliminate code duplication and improve maintainability while preserving all original functionality.

**Note on Unimplemented Classes:**
Several classes remain in the codebase (visible in CMake configuration) that were originally planned but not fully implemented due to project scope and time constraints. These include:
- Power-up system classes (PowerUp, Shield, SpeedBoost, TimeBonus)
- Additional vehicle types (Motorcycle, Truck)
- Advanced obstacle types (MovingPedestrian, RoadBoundary)
- CollisionManager (superseded by current collision system)

These classes could not be removed from the build system due to CMake dependencies but do not affect the functional game implementation.

**Key Technical Achievements:**
- Successful integration of SFML graphics with Box2D physics engine
- Implementation of multiple design patterns for clean, maintainable code
- Event-driven architecture enabling loose coupling between system components
- Comprehensive JSON-based level loading system
- Professional exception handling with detailed error context
- Resource management ensuring efficient memory usage and cleanup
