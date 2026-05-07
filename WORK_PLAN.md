# cub3D Work Plan

## Goal

This document defines how Mario and Manuel will split the work for `cub3D`. The goal is to keep the workload balanced while matching each person's strengths: Mario will focus mainly on the mathematical and rendering side, while Manuel will focus mainly on parsing and validation.

Both parts are equally important. A correct parser is required before rendering can start safely, and a correct raycaster is required for the final visual result.

## Mario Responsibilities

Mario will focus on the math-heavy and graphics-heavy parts of the project.

### Raycasting

- Define the player position, direction vector, and camera plane.
- Implement the ray loop for each vertical stripe of the screen.
- Calculate ray direction for every column.
- Calculate `delta_dist_x` and `delta_dist_y`.
- Calculate `side_dist_x` and `side_dist_y`.
- Implement the DDA algorithm to detect wall hits.
- Calculate perpendicular wall distance to avoid fisheye distortion.
- Calculate wall height, draw start, and draw end.

### Rendering

- Draw ceiling and floor colors.
- Draw wall slices based on raycasting results.
- Select the correct texture depending on wall direction: North, South, East, or West.
- Calculate texture X and Y coordinates.
- Put pixels into the MLX image buffer efficiently.
- Render the final image to the window.

### Movement and Camera

- Implement player rotation with the left and right arrow keys.
- Implement movement with `W`, `A`, `S`, and `D`.
- Add wall collision handling for movement.
- Tune movement speed and rotation speed.
- Make movement feel smooth and predictable.

### Math Testing

- Test the raycaster with small maps.
- Check edge cases when rays hit horizontal or vertical walls.
- Verify that the player orientation matches `N`, `S`, `E`, and `W`.
- Check that texture orientation is correct on all wall sides.

## Manuel Responsibilities

Manuel will focus on parsing, validation, and preparing clean data for the rest of the program.

### File Reading

- Validate that the program receives exactly one argument.
- Validate that the argument has the `.cub` extension.
- Open and read the `.cub` file safely.
- Store the file content in a structure that can be parsed later.
- Handle empty files and read errors cleanly.

### Configuration Parsing

- Parse texture identifiers: `NO`, `SO`, `WE`, and `EA`.
- Validate texture paths.
- Detect missing texture paths.
- Detect duplicate texture identifiers.
- Parse floor color with identifier `F`.
- Parse ceiling color with identifier `C`.
- Validate RGB format: `R,G,B`.
- Validate RGB range: `0` to `255`.
- Reject invalid characters or extra data in configuration lines.

### Map Parsing

- Detect where the map starts.
- Ensure the map is the last part of the file.
- Preserve spaces inside the map.
- Validate allowed map characters: `0`, `1`, spaces, `N`, `S`, `E`, and `W`.
- Validate that there is exactly one player start position.
- Store the player's initial position and orientation.
- Convert the map into a format usable by the raycaster.

### Map Validation

- Validate that the map is closed by walls.
- Handle irregular map shapes.
- Treat spaces correctly as outside/void areas.
- Detect open borders next to `0` or player position.
- Return clear errors for invalid maps.

### Error Handling and Cleanup

- Print `Error\n` followed by an explicit error message.
- Free all memory allocated during parsing when an error happens.
- Prepare cleanup functions for parsed data.
- Make parser failures predictable and easy to debug.

## Shared Responsibilities

Some parts should be designed and reviewed together because both sides depend on them.

### Project Architecture

- Agree on the main structs before implementing too much code.
- Define structs for game state, map, player, textures, colors, and MLX context.
- Agree on which module owns each allocation.
- Keep headers clear and not overloaded.

### Makefile and Norm

- Create and maintain the `Makefile`.
- Ensure the project compiles with `-Wall`, `-Wextra`, and `-Werror`.
- Avoid unnecessary relinking.
- Run Norm checks regularly.
- Keep functions short and readable.

### miniLibX Setup

- Initialize MLX and the window.
- Load XPM textures.
- Create and manage image buffers.
- Handle keyboard events.
- Handle window close events.
- Destroy images and the window on exit.

### Testing

- Create valid maps for normal testing.
- Create invalid maps for parser testing.
- Test missing textures, bad colors, invalid characters, and open maps.
- Test player movement near walls.
- Test all player starting orientations.
- Test clean exit with `ESC` and the window close button.
- Check memory leaks.

### Code Review

- Mario reviews Manuel's parser from the point of view of what the renderer needs.
- Manuel reviews Mario's rendering code from the point of view of data assumptions and edge cases.
- No major feature should be merged into `main` without being compiled and tested.

## Balanced Milestones

### Milestone 1: Base Setup

- Mario: create initial MLX window and image buffer.
- Manuel: create file reading and basic `.cub` argument validation.
- Shared: define main structs and Makefile.

### Milestone 2: Parser and Static Render

- Mario: draw floor, ceiling, and a simple placeholder wall render.
- Manuel: parse textures, colors, and map into final structs.
- Shared: connect parser output with renderer input.

### Milestone 3: Raycasting and Map Validation

- Mario: implement DDA raycasting and wall projection.
- Manuel: complete map closure validation and player start validation.
- Shared: test with multiple valid and invalid maps.

### Milestone 4: Textures and Controls

- Mario: apply wall textures and implement movement/rotation.
- Manuel: strengthen parser errors and cleanup paths.
- Shared: test texture directions, controls, and clean exits.

### Milestone 5: Polish and Defense Preparation

- Mario: tune rendering, movement, and collision behavior.
- Manuel: finalize error messages and parser edge cases.
- Shared: run Norm, leak checks, defense tests, and explain each module to each other.

## Branches

- `main`: stable branch with reviewed code only.
- `mario`: Mario's branch for raycasting, rendering, movement, and math.
- `manuel`: Manuel's branch for parsing, validation, file handling, and errors.

Recommended workflow:

```sh
git switch mario
# Mario works on rendering/math
```

```sh
git switch manuel
# Manuel works on parsing/validation
```

Before merging into `main`, both should compile, test, and review the change.

## Final Responsibility Split

| Area | Main Owner | Reviewer |
| --- | --- | --- |
| Raycasting | Mario | Manuel |
| Rendering | Mario | Manuel |
| Movement and rotation | Mario | Manuel |
| File parsing | Manuel | Mario |
| Map validation | Manuel | Mario |
| Error handling | Manuel | Mario |
| Makefile | Shared | Shared |
| MLX setup | Shared | Shared |
| Testing | Shared | Shared |
| Defense preparation | Shared | Shared |
