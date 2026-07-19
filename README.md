*This project has been created as part of the 42 curriculum by moodeh, samarnah.*

# Cub3D

## Description

Cub3D is a raycasting engine inspired by the classic Wolfenstein 3D game. It renders a 3D perspective view of a 2D map using the DDA (Digital Differential Analyzer) algorithm to cast rays from the player's viewpoint, determining wall distances and textures to produce a pseudo-3D environment. The project demonstrates fundamental concepts of computer graphics, including raycasting, texture mapping, and real-time rendering.

## Features

- **Raycasting Engine**: DDA-based raycasting for efficient wall detection
- **Textured Walls**: Support for four directional textures (North, South, East, West)
- **Player Movement**: WASD keys for movement, arrow keys for rotation
- **Collision Detection**: Hitbox-based wall collision system
- **Minimap**: Real-time 2D minimap overlay
- **Floor & Ceiling Colors**: Configurable RGB colors for floor and ceiling

## Instructions

### Prerequisites

- Linux with X11 development libraries
- `gcc` compiler
- `make`

### Compilation

```bash
make
```

### Execution

```bash
./cub3D maps/good/subject_map.cub
```

### Map Format

Maps use the `.cub` extension and follow this format:

```
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

F 220,100,0
C 225,30,0

    1111111
    1000001
    1000001
11110000011
1000000N001
10000000001
11111111111
```

- `NO`, `SO`, `WE`, `EA`: Wall texture paths
- `F`: Floor color (R,G,B)
- `C`: Ceiling color (R,G,B)
- `1`: Wall
- `0`: Empty space
- `N`, `S`, `W`, `E`: Player spawn position and facing direction

### Controls

| Key | Action |
|-----|--------|
| W | Move forward |
| S | Move backward |
| A | Strafe left |
| D | Strafe right |
| Left Arrow | Rotate left |
| Right Arrow | Rotate right |
| ESC | Exit game |

## Project Structure

```
Cub3D/
├── Include/          # Header files
├── src/
│   ├── main.c        # Entry point
│   ├── error/        # Error handling
│   ├── parsing/      # Map parsing and validation
│   ├── player/       # Player movement and rotation
│   ├── render/       # Raycasting and rendering
│   └── utils/        # Helper functions, hooks, textures
├── libft/            # Custom C library
├── minilibx-linux/   # MiniLibX graphics library
├── get_next_line/    # Get next line utility
└── maps/             # Sample maps
```

## Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Comprehensive raycasting guide
- [DDA Algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) - Wikipedia reference
- [MiniLibX Documentation](https://github.com/42Paris/minilibx-linux) - Graphics library used
- [Wolfenstein 3D Technical Reference](https://www.idsoftware.com/category/wolfenstein-3d/) - Original game reference

## AI Usage

AI tools were used during the development of this project for the following purposes:

- **Debugging**: Assisted in identifying and fixing issues in the DDA raycasting algorithm and rendering pipeline
- **Code Review**: Helped review code structure and suggest improvements for readability and maintainability
- **Documentation**: Assisted in writing explanatory comments for complex mathematical operations in the rendering code
- **Learning Support**: Provided explanations of raycasting concepts, vector mathematics, and graphics programming techniques
