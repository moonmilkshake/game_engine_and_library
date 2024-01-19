# game_engine_and_library

Overview
This project includes a 2D top-down game engine developed in C++ using SDL2 and a basic library to work with. It is designed to power games with features like collision detection, easy memory clean up, obstacle interaction, handling of animation, attacks, and more. Perfect for developers looking to build simple games.

Game Engine Features
These features are part of the game engine and can be utilized by any game developed using this engine.
- Efficient Game Loop: Maintains a consistent frame rate and processes user input effectively.
- Component-Based Architecture: Facilitates easy addition and management of game entities and features.
- Dynamic Collision Detection & Handling: Offers a system for detecting and responding to collisions between game entities.
- Use of UI Components: Supports the creation and integration of interactive UI elements for diverse player interactions. UI can be set up to pause game as needed.
- Modular Design: Allows developers to easily plug in new types of player characters, enemies, obstacles and more.

Sample Game Features
The following features are specific to the sample game built using this game engine.
- Playable Character: A character that players can control, featuring basic movement and interaction abilities.
- Elemental Attacks: Unique player abilities, including Stone, Magma, and Ice attacks, each with distinct effects.
- Enemy Types: Various monsters with different behaviors and challenges.
- Interactive Environment: An environment that responds to player actions and enemy movements.
- Animations: Simple animations of all sprites powered through the game engine.

Getting Started
Prerequisites
- SDL2 Library.
- C++ Compiler.
- Basic understanding of C++ and game development concepts.

Installation
- Clone the repository:
  - git clone https://github.com/moonmilkshake/game_engine_and_library
- Navigate to the cloned directory and compile the source code.
  - Compiler, flags and paths need to be set to the users specific requierments in their IDE.

Run the compiled executable:
- By use of command "make" the program will be compiled and can be found in specified path build/debug
- Execute the game by use of ./build/debug/play

Usage
- Starting the Engine: By instantiating the GameEngine class and executing engineInstance.run()
- Adding New Components:
  - Add components by instantiating/subclassing desired class in the Sprites-hierarchy. Component acts as the base-class.
  - Add the sprite to engineInstance.addGameComponent(spriteInstance).
  - UI-components are added by use of .addUIComponent(uiComponentInstance).
  - Removal of components: .removeGameComponent(spriteInstance) or .removeUIComponent(uiComponentInstance).
- Player Controls: Basic inputs are handled in the GameEngine loop. For extra customization, inputs can be implemented in the MovableSprite class and overriden in desired subclass for specific handling.

License
- This project is licensed - see the LICENSE.md file for details.
