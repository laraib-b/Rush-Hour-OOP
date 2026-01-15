# Rush Hour Game

A 2D grid-based driving game built with C++ using Object-Oriented Programming concepts and GLUT libraries. Navigate through a randomly generated city as either a Taxi Driver or Delivery Rider, pick up passengers/packages, and deliver them to their destinations while managing fuel and money.

## Game Overview

**Rush Hour** is a time-based driving game where you play as either:
- **Taxi Driver** (Yellow Car): Pick up passengers and drop them at their destinations
- **Delivery Rider** (Red Car): Pick up packages and deliver them to their destinations

Your goal is to maximize your score within the 180-second time limit while managing fuel and avoiding obstacles.

## Game Features

- **Two Game Modes**: Choose between Taxi Driver or Delivery Rider
- **Random Map Generation**: Each game features a procedurally generated city grid
- **Fuel Management**: Refuel at fuel stations to keep driving
- **Score System**: Earn points by completing deliveries, lose points for collisions
- **Leaderboard**: Track top 10 scores with player names
- **Time Limit**: 180 seconds to complete as many deliveries as possible

## Prerequisites

This game currently runs on **Ubuntu/Linux** systems. You'll need:

- C++ compiler (g++)
- Make build tool
- GLUT (OpenGL Utility Toolkit)
- FreeImage library
- GLEW library

## Installation

### Step 1: Install Required Libraries

Run the provided installation script:

```bash
chmod +x install-libraries.sh
./install-libraries.sh
```

Or manually install dependencies:

```bash
sudo apt-get update
sudo apt-get install make freeglut3-dev glew-utils libglew-dev libfreeimage-dev
```

### Step 2: Build the Game

Compile the game using the Makefile:

```bash
make clean
make
```

This will create an executable named `game`.

## Running the Game

After successful compilation, run the game:

```bash
./game
```

## How to Play

### Starting the Game

1. **Enter Your Name**: When the game starts, click on the text field and type your name, then press `Enter`
2. **Choose Game Mode**: 
   - Click "Taxi Driver" to play as a taxi driver
   - Click "Delivery Packages Rider" to play as a delivery rider
   - Click "Randomize?" for a random mode selection

### Controls

- **Arrow Keys**: Move your vehicle (Up, Down, Left, Right)
- **Spacebar**: Pick up passenger/package (when adjacent to one)
- **D**: Drop passenger/package at destination
- **F**: Refuel at fuel station (when standing on one)
- **R**: Reset/randomize the current map
- **B**: Go back to main menu
- **P**: Switch role (return to garage)
- **ESC**: Exit the game

### Gameplay Mechanics

#### As Taxi Driver:
- **Pick up passengers** (purple figures) using Spacebar when adjacent
- **Drop passengers** at green highlighted destinations using D key
- Earn money based on distance traveled
- Avoid hitting NPCs (black figures) - lose 5 points
- Avoid hitting buildings - lose 1 point

#### As Delivery Rider:
- **Pick up packages** (khaki boxes) using Spacebar when adjacent
- **Drop packages** at salmon-colored destinations using D key
- Earn money based on distance traveled
- Avoid hitting NPCs - lose 8 points
- Avoid hitting buildings - lose 4 points

#### General Rules:
- **Fuel**: Each movement consumes 0.25 fuel units
- **Refueling**: Stand on a blue fuel station and press F to refuel (costs money)
- **Score**: 
  - Complete deliveries: +10 points (taxi) or +20 points (delivery)
  - Score > 100: Win condition
  - Score < 0: Game Over
  - Fuel = 0: Game Over
- **Time**: 180 seconds countdown timer

### Game Elements

- **White Squares**: Roads (safe to drive on)
- **Black Squares**: Buildings (avoid - lose points)
- **Blue Squares**: Fuel stations (refuel here)
- **Green Circles**: Trees (obstacles)
- **Brown/Gray Squares**: Obstacles
- **Purple Figures**: Passengers (Taxi mode)
- **Khaki Boxes**: Packages (Delivery mode)
- **Green Highlighted Cells**: Passenger destinations (Taxi mode)
- **Salmon Highlighted Cells**: Package destinations (Delivery mode)
- **Pink House**: Garage (starting point)

## Leaderboard

- Access the leaderboard from the main menu or after game over
- Top 10 scores are saved to `scores.dat`
- Scores are sorted in descending order
- Your score is automatically saved if it qualifies for top 10

## Project Structure

```
Rush-Hour-OOP-main/
├── game.cpp          # Main game logic and OOP classes
├── util.cpp          # Utility functions for drawing
├── util.h            # Header file with utility declarations
├── CImg.h            # Image processing library header
├── Makefile          # Build configuration
├── install-libraries.sh  # Dependency installation script
└── scores.dat        # Leaderboard data file (created after first game)
```

## OOP Concepts Used

The project demonstrates several Object-Oriented Programming principles:

- **Inheritance**: `Vehicle` → `PlayerCar`, `Obstacles` → `Trees`, `Person` → `NPCperson`/`Passenger`
- **Polymorphism**: Virtual functions (`drawCar()`, `draw()`)
- **Abstract Classes**: `Vehicle` class with pure virtual function
- **Encapsulation**: Private/protected members in classes
- **Classes**: `Player`, `BoardMap`, `Game`, `Menu`, `LeaderBoard`, `FuelStation`, `Garage`, etc.

## Troubleshooting

### Game won't compile
- Ensure all dependencies are installed: `sudo apt-get install make freeglut3-dev glew-utils libglew-dev libfreeimage-dev`
- Check that you're using a compatible C++ compiler

### Game crashes on startup
- Verify X11 display is available (for Linux GUI)
- Check that GLUT libraries are properly installed

### Can't see the game window
- Ensure you're running on a system with X11/Wayland display server
- Check display permissions if running via SSH

## Notes

- The game uses OpenGL for rendering
- Map generation uses random seed based on current time
- Leaderboard data is stored in binary format in `scores.dat`
- Game window size: 1000x840 pixels

## Author

Developed as an OOP project (Student ID: 24I-2544)

## License

Copyright (c) Reserved

---

**Enjoy playing Rush Hour!**
