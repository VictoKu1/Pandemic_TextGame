# Pandemic Text Game

A C++ implementation of the Pandemic board game as a text-based simulation. This project demonstrates object-oriented programming principles through the implementation of various player roles, game mechanics, and board management.

## Table of Contents

- [Task Overview](#task-overview)
- [Project Structure](#project-structure)
- [Solution Architecture](#solution-architecture)
- [Game Mechanics](#game-mechanics)
- [Player Roles](#player-roles)
- [Implementation Details](#implementation-details)
- [Building and Testing](#building-and-testing)
- [Usage](#usage)

## Task Overview

The task involves implementing a single-player version of the Pandemic board game in C++. The goal is to create a system that simulates the core mechanics of the original game, including:

- **Board Management**: A world map with 48 cities divided into 4 colors (blue, yellow, black, red)
- **Disease Management**: Tracking disease cubes across cities
- **Player Actions**: Movement, building research stations, discovering cures, and treating diseases
- **Role System**: 8 different player roles with unique abilities
- **Game State**: Managing research stations, discovered cures, and disease outbreaks

The implementation must pass all provided tests and demonstrate clean, maintainable C++ code following modern standards.

## Project Structure

```
Pandemic_TextGame/
├── Main.cpp                 # Main game executable
├── TestRunner.cpp           # Test framework
├── Makefile                 # Build configuration
├── cities_map.txt          # City connections data
├── sources/                 # Source files
│   ├── Board.hpp/cpp       # Game board implementation
│   ├── City.hpp            # City enumeration
│   ├── Color.hpp           # Color enumeration
│   ├── Player.hpp/cpp      # Base player class
│   ├── [Role].hpp/cpp      # Player role implementations
└── objects/                # Compiled objects
```

## Solution Architecture

### Core Design Patterns

1. **Inheritance Hierarchy**: All player roles inherit from a base `Player` class
2. **Polymorphism**: Different player types can perform the same actions with role-specific modifications
3. **Encapsulation**: Game state is managed through the `Board` class
4. **Exception Handling**: Comprehensive error checking for invalid game actions

### Key Classes

#### Board Class
- Manages the game world state
- Tracks disease cubes in each city
- Manages research stations and discovered cures
- Provides operator overloads for easy city access

#### Player Class (Base)
- Abstract base class for all player types
- Defines common player actions (drive, fly, build, treat, etc.)
- Manages player location and card inventory

#### Role-Specific Classes
- **OperationsExpert**: Can build research stations without discarding city cards
- **Dispatcher**: Enhanced flight abilities when at research stations
- **Scientist**: Can discover cures with fewer cards
- **Researcher**: Can discover cures anywhere (not just at research stations)
- **Medic**: Enhanced disease treatment abilities
- **Virologist**: Can treat diseases remotely using city cards
- **GeneSplicer**: Can discover cures using any combination of cards
- **FieldDoctor**: Can treat diseases in adjacent cities

## Game Mechanics

### Board Representation
- 48 cities organized by color (12 cities per color)
- Cities connected by travel routes
- Disease cubes tracked per city
- Research stations and cures tracked globally

### Player Actions
1. **Drive**: Move to adjacent cities
2. **Direct Flight**: Fly to any city using a city card
3. **Charter Flight**: Fly anywhere by discarding current city's card
4. **Shuttle Flight**: Fly between research stations
5. **Build**: Construct a research station (requires city card)
6. **Discover Cure**: Find cure for a disease color (requires 5 cards + research station)
7. **Treat**: Remove disease cubes from current city

### Game State Management
- Disease cube tracking with automatic outbreak prevention
- Research station placement and management
- Cure discovery and application
- Player location and card inventory tracking

## Player Roles

### OperationsExpert
- **Special Ability**: Build research stations without discarding city cards
- **Strategy**: Efficient research station network building

### Dispatcher
- **Special Ability**: Enhanced direct flight when at research stations
- **Strategy**: Rapid response and movement coordination

### Scientist
- **Special Ability**: Discover cures with N cards instead of 5
- **Strategy**: Faster cure discovery, especially valuable for rare diseases

### Researcher
- **Special Ability**: Discover cures anywhere (not just at research stations)
- **Strategy**: Flexible cure discovery without travel constraints

### Medic
- **Special Ability**: Remove all disease cubes when treating, automatic cube removal when entering cities with cured diseases
- **Strategy**: Efficient disease containment and cleanup

### Virologist
- **Special Ability**: Treat diseases remotely using city cards
- **Strategy**: Remote disease treatment without travel

### GeneSplicer
- **Special Ability**: Discover cures using any 5 cards (not just matching color)
- **Strategy**: Flexible cure discovery with any card combination

### FieldDoctor
- **Special Ability**: Treat diseases in adjacent cities
- **Strategy**: Local disease control without card costs

## Implementation Details

### Memory Management
- Smart pointer usage where appropriate
- RAII principles for resource management
- Proper cleanup in destructors

### Error Handling
- Comprehensive exception throwing for invalid actions
- Clear error messages for debugging
- Graceful handling of edge cases

### Code Quality
- Modern C++ standards (C++20)
- Consistent naming conventions
- Comprehensive documentation
- Unit test coverage

### Performance Considerations
- Efficient data structures for city connections
- Minimal memory allocation during gameplay
- Optimized lookup operations

## Building and Testing

### Prerequisites
- C++20 compatible compiler (clang++-9 recommended)
- Make utility
- Valgrind (for memory checking)

### Build Commands
```bash
# Build all tests
make test1 && ./test1
make test2 && ./test2
make test3 && ./test3

# Code quality checks
make tidy
make valgrind

# Build main game
make Main
```

### Test Structure
- **test1**: Basic functionality tests
- **test2**: Advanced game mechanics
- **test3**: Edge cases and error conditions
- **valgrind**: Memory leak detection
- **tidy**: Code style and quality checks

## Usage

### Running the Game
```bash
make Main
./Main
```

### Game Flow
1. Choose your player role
2. Start in a random city
3. Perform actions to contain diseases and discover cures
4. Win by discovering all cures or lose if diseases spread too much

### Controls
- Numeric input for menu selections
- City selection by number (0-47)
- Automatic validation of all actions

### Game Features
- Interactive text-based interface
- Real-time board state display
- Comprehensive action validation
- Role-specific ability demonstration

This implementation provides a complete, playable version of Pandemic that demonstrates advanced C++ programming concepts while maintaining the strategic depth of the original board game. 