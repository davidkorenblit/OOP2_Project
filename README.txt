2D Physics Parking Simulator
High-Performance C++ Simulation with Box2D and SFML

Overview
A 2D vehicle simulation built from the ground up, focusing on architectural integrity and realistic physics. The project demonstrates advanced Object-Oriented Programming (OOP) in C++, event-driven communication, and efficient resource management.

Key Features
* Realistic Physics: Integrated Box2D engine for friction, momentum, and collision responses.
* Progressive Difficulty: Dynamic level loading system with static and dynamic obstacles.
* Scalable Architecture: Modular manager-based design for decoupling game logic from rendering.
* Robust Memory Management: 100% RAII compliant using smart pointers (unique_ptr).

---

System Architecture
The system is built on a Decoupled Manager Architecture, ensuring high maintainability and separation of concerns.

* GameManager: The central orchestrator managing game states (FSM) and the main loop.
* LevelManager: Controls the lifecycle of active game objects and physics step updates.
* ObjectFactory: A centralized JSON-driven creation system for level instantiation.
* Resource Managers: Singleton-based handlers for Texture and Sound caching to optimize memory footprint.

---

Design Patterns Implemented
This project serves as a practical implementation of industry-standard design patterns:

| Pattern | Usage in Project |
| :--- | :--- |
| Visitor | Used in the collision system (acceptCollision) to resolve double-dispatching between game objects. |
| Observer | Event-driven communication between LevelManager and GameManager for loose coupling. |
| Singleton | Ensures global access and single-instance integrity for TextureManager and SoundManager. |
| Factory | Centralized object creation from JSON configuration files. |
| State | Managing complex UI and game transitions such as Menu, Play, Pause, and Game Over. |
| Template Method | Defined in the Vehicle hierarchy to share physics logic while allowing specialized behavior. |

---

Technical Highlights

Collision and Physics
* Implemented AABB collision detection with object-type-specific expanded bounding boxes.
* Custom Exception Handling hierarchy (GameException) for resource loading and level data corruption.

Data Structures and Memory
* Smart Pointers: Extensive use of std::unique_ptr for automatic memory management.
* Efficient Caching: std::map based caching for textures and audio buffers to prevent redundant I/O operations.
* Vectorization: All game entities are managed via polymorphic std::vector collections.

---

Getting Started

Prerequisites
* C++17 Compiler.
* SFML 2.5+.
* Box2D.

Installation
```bash
git clone [https://github.com/davidkorenblit/parking-2d-game.git](https://github.com/davidkorenblit/parking-2d-game.git)
mkdir build && cd build
cmake ..
make
./ParkingGame
