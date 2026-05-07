*This project has been created as part of the 42 curriculum by mario, manuel.*

# cub3D

## Description

`cub3D` is a 42 school graphics project inspired by Wolfenstein 3D, one of the first first-person shooter games. The goal is to render a realistic first-person view inside a maze using ray-casting principles and the miniLibX graphics library.

The program reads a `.cub` scene file, validates its configuration, loads wall textures, applies floor and ceiling colors, and displays the maze from the player's point of view. The player can move through the map and rotate the camera using the keyboard.

## Mandatory Features

- Written in C and compliant with the 42 Norm.
- Built with a `Makefile` using `cc`, `-Wall`, `-Wextra`, and `-Werror`.
- Uses miniLibX for window management, images, textures, and events.
- Reads one `.cub` map file passed as the first argument.
- Parses and validates texture paths for North, South, West, and East walls.
- Parses and validates floor and ceiling RGB colors.
- Validates that the map is closed and contains exactly one player start position.
- Supports player movement with `W`, `A`, `S`, and `D`.
- Supports camera rotation with the left and right arrow keys.
- Exits cleanly with `ESC` or by closing the window.
- Frees allocated memory and handles errors with `Error\n` followed by an explicit message.

## Instructions

### Compilation

```sh
make
```

This must generate the executable:

```sh
./cub3D
```

Useful Makefile rules:

```sh
make all
make clean
make fclean
make re
make bonus
```

### Execution

Run the program with a valid `.cub` scene file:

```sh
./cub3D maps/example.cub
```

Example minimal scene file:

```cub
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

### Controls

| Key | Action |
| --- | --- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `Left Arrow` | Rotate camera left |
| `Right Arrow` | Rotate camera right |
| `ESC` | Exit the program |

## Work Plan

### Mario: Raycasting, Math, and Rendering

- Define the player position, direction vector, and camera plane.
- Implement the ray-casting loop for every vertical screen stripe.
- Calculate ray direction, delta distance, side distance, DDA steps, wall hit detection, and perpendicular wall distance.
- Compute wall height, draw start, draw end, and texture coordinates.
- Apply different textures depending on the wall side: North, South, East, or West.
- Implement smooth movement, rotation, and collision checks.
- Tune movement speed, rotation speed, and rendering performance.

### Manuel: Parsing, Validation, and Data Setup

- Read the `.cub` file safely and store its lines.
- Parse texture identifiers: `NO`, `SO`, `WE`, and `EA`.
- Parse floor and ceiling colors: `F` and `C`.
- Validate RGB values, duplicate identifiers, missing fields, and invalid extra data.
- Detect the map start and ensure the map is the last section of the file.
- Validate allowed map characters: `0`, `1`, spaces, `N`, `S`, `E`, and `W`.
- Ensure there is exactly one player start position.
- Validate that the map is closed, including irregular shapes and spaces.
- Prepare clean error messages and cleanup paths for invalid files.

### Shared Tasks

- Define common structs for game state, textures, map, player, and MLX context.
- Agree on ownership rules for allocated memory.
- Write small invalid and valid `.cub` test files.
- Run Norm checks regularly.
- Test leaks and clean program exits.
- Review each other's code before merging.

## Suggested Branch Strategy

- `main`: stable branch with reviewed and working code.
- `mario`: raycasting, rendering, movement, and math-heavy features.
- `manuel`: parser, file validation, map validation, and configuration loading.

Recommended flow:

```sh
git switch main
git pull
git switch mario
# work on raycasting/rendering
git merge main
```

```sh
git switch main
git pull
git switch manuel
# work on parsing/validation
git merge main
```

When a feature is complete, open a merge request or merge only after review and testing.

## Project Structure Proposal

```text
.
├── includes/
├── libft/
├── maps/
├── src/
│   ├── main.c
│   ├── parsing/
│   ├── rendering/
│   ├── events/
│   └── cleanup/
├── textures/
├── Makefile
└── README.md
```

## Resources

- 42 cub3D subject, version 12.0.
- miniLibX documentation and examples.
- Lode Vandevenne's raycasting tutorial: https://lodev.org/cgtutor/raycasting.html
- Wolfenstein 3D technical background: https://en.wikipedia.org/wiki/Wolfenstein_3D
- `man 3 math` for trigonometric and math library functions.
- `man gettimeofday` for time-based movement or frame calculations.

## AI Usage

AI was used to help create this README, organize the project plan, summarize the subject requirements, and propose a collaboration split between parsing and raycasting tasks.

AI should not be used to blindly generate final project code. Any AI-assisted idea or snippet must be reviewed, understood, tested, and explained by the team before being included in the project.
