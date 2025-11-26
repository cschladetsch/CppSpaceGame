# SpaceGame

A voxel-based space simulator built with C++, SDL3, and GLM. Features procedurally generated starships rendered using a custom voxel engine.

## Features

- Voxel-based spaceship models with multiple component types (hull, engines, thrusters, weapons, armor, systems)
- Real-time 3D rendering using SDL3
- Fully controllable camera with WASD movement and arrow key rotation
- Dynamic ship positioning and rotation
- Ship model serialization (binary format)
- Includes an Enterprise-style ship generator

## Dependencies

- C++17 or later
- CMake 3.20+
- SDL3 (automatically fetched if not found)
- GLM 0.9.9.8+ (automatically fetched if not found)

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

The executable will be placed in the `bin/` directory.

## Running

First, generate a ship model:

```bash
./bin/create_ship
```

This creates `data/ship.bin` containing a voxel model.

Then run the main game:

```bash
./bin/SpaceGame
```

## Controls

- **W/S**: Move camera forward/backward
- **A/D**: Move camera left/right
- **Arrow Keys**: Rotate camera view
- **ESC**: Quit (window close button)

## Project Structure

- `src/` - Core game source files
  - `main.cpp` - Entry point and game loop
  - `voxel.h/cpp` - Voxel model system
  - `ship.h/cpp` - Ship entity implementation
  - `entity.h/cpp` - Base entity class
  - `renderer.h/cpp` - Rendering system
  - `camera.h/cpp` - Camera controls
- `data/` - Runtime data files (ship models)
- `create_ship.cpp` - Ship model generator utility

## Technical Details

The engine uses a voxel-based representation where ships are composed of individual colored cubes. Each voxel has:
- 3D position (int16)
- Type (hull, engine, thruster, weapon, armor, system)
- RGBA color
- Health value (for damage modeling)

Models are stored in a binary format for efficient loading.
