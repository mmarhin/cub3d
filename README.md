*This project has been created as part of the 42 curriculum by mamarin-, mruiz-ur.*

# cub3D

## Description

`cub3D` is a 42 school graphics project inspired by Wolfenstein 3D, one of the first first-person shooter games. The main goal is to render a realistic first-person view inside a maze using ray-casting principles and the miniLibX graphics library.

The program reads a `.cub` scene file, validates its configuration, loads wall textures, applies floor and ceiling colors, and displays the maze from the player's point of view. The player can move through the map and rotate the camera using the keyboard.

## Instructions

### Compilation

To compile the project, run the following command at the root of the repository:

```sh
make
```

This will generate the `cub3D` executable. Other useful Makefile rules include:
- `make clean`: Removes object files.
- `make fclean`: Removes object files and the executable.
- `make re`: Recompiles the project from scratch.

### Execution

Run the program by passing a valid `.cub` scene file as the first and only argument:

```sh
./cub3D maps/valid_simple.cub
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
| `ESC` or `Red Cross` | Exit the program cleanly |

## Resources

**Classic References:**
- 42 cub3D subject, version 12.0.
- miniLibX documentation and examples.
- Lode Vandevenne's Raycasting Tutorial: https://lodev.org/cgtutor/raycasting.html
- Wolfenstein 3D technical background: https://en.wikipedia.org/wiki/Wolfenstein_3D
- `man 3 math` for trigonometric and mathematical functions.

**AI Usage:**
AI was used as a supportive tool to help structure the raycasting logic, better understand memory leaks reported by Valgrind regarding miniLibX, and generate initial map validation logic outlines. At no point was AI used to blindly generate final code; all responses were reviewed, tested, and deeply understood by the team (mamarin- and mruiz-ur) before being integrated into the project.
