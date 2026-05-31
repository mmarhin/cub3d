# cub3D – Work Plan

## Goal

This document defines how Mario and Manuel will split the work for `cub3D`.
The subject requires a realistic 3-D first-person view of a maze using
ray-casting principles and the miniLibX graphics library.

---

## Subject constraints (always keep in mind)

| Rule | Detail |
|---|---|
| Language | C, 42 Norm |
| Compilation | `cc -Wall -Wextra -Werror` |
| Library | miniLibX only (no other graphics) |
| Argument | exactly one `.cub` scene file |
| Textures | NO / SO / WE / EA – one XPM per wall side |
| Colors | F (floor) and C (ceiling) as `R,G,B` in `[0,255]` |
| Map chars | `0` `1` `N` `S` `E` `W` and spaces only |
| Map rule | must be **closed** (surrounded by `1` walls) |
| Player | exactly **one** start position (N/S/E/W) |
| Controls | WASD move · arrows rotate · ESC exits · red-cross exits |
| Errors | `Error\n` + explicit message on any misconfiguration |
| Memory | all allocations freed on exit or error |

---

## Project structure

```
cub3d/
├── includes/
│   └── cub3d.h              ← all structs + all prototypes
├── src/
│   ├── main.c
│   ├── parsing/             ← Manuel
│   │   ├── parse_args.c
│   │   ├── read_file.c
│   │   ├── parse_textures.c
│   │   ├── parse_colors.c
│   │   ├── parse_map.c
│   │   └── validate_map.c
│   ├── rendering/           ← Mario
│   │   ├── init_mlx.c
│   │   ├── load_textures.c
│   │   ├── raycasting.c
│   │   ├── draw.c
│   │   └── texture_utils.c
│   ├── events/              ← Mario
│   │   ├── hooks.c
│   │   └── move.c
│   ├── cleanup/             ← shared
│   │   └── cleanup.c
│   └── utils/               ← Manuel
│       └── error.c
├── maps/
│   ├── valid_simple.cub
│   ├── valid_complex.cub
│   ├── invalid_open.cub
│   ├── invalid_color.cub
│   └── invalid_missing_tex.cub
├── textures/                ← add .xpm files here
├── libft/                   ← copy your libft here
├── mlx/                     ← copy miniLibX here
├── Makefile
├── README.md
└── WORK_PLAN.md
```

---

## Mario – Rendering, Raycasting, Events

### Milestone 1 · MLX + window
**File:** `src/rendering/init_mlx.c`
- [ ] `mlx_init()` + `mlx_new_window()`
- [ ] Create image buffer with `mlx_new_image` + `mlx_get_data_addr`
- [ ] Verify window opens, image renders, and window can be minimised/switched

### Milestone 2 · Static render (floor + ceiling)
**File:** `src/rendering/draw.c`
- [ ] `draw_background` – fill top half with ceiling color, bottom with floor color
- [ ] Use `t_color` values from Manuel's parser (RGB → `(r<<16)|(g<<8)|b`)
- [ ] `render_frame` → `draw_background` + `mlx_put_image_to_window`

### Milestone 3 · Raycasting – DDA
**File:** `src/rendering/raycasting.c`
- [ ] `camera_x` in `[-1, 1]` per screen column
- [ ] `ray_dir_x/y` from `dir + plane * camera_x`
- [ ] `delta_dist` (avoid div-by-zero)
- [ ] `step` and initial `side_dist`
- [ ] DDA loop until `map[map_x][map_y] == '1'`
- [ ] `perp_wall_dist` (correct fisheye)
- [ ] `line_height`, `draw_start`, `draw_end`

### Milestone 4 · Textured walls
**Files:** `src/rendering/draw.c` · `src/rendering/texture_utils.c`
- [ ] Select texture by wall side: `side==1 && ray_dir_y<0` → NO, etc.
- [ ] `calc_tex_x` – fractional wall hit → column in XPM
- [ ] `draw_wall_slice` – sample texture per pixel in `[draw_start, draw_end]`
- [ ] `get_tex_color` – `addr + y*line_len + x*(bpp/8)` cast to int

### Milestone 5 · Load XPM textures
**File:** `src/rendering/load_textures.c`
- [ ] `mlx_xpm_file_to_image` for NO / SO / WE / EA
- [ ] Store `width`, `height`, `addr`, `bpp`, `line_len`, `endian` in `t_tex`
- [ ] Return error if any texture path is missing or file not found

### Milestone 6 · Movement + rotation + collision
**Files:** `src/events/hooks.c` · `src/events/move.c`
- [ ] `handle_keydown` – dispatch ESC / arrows / WASD
- [ ] `handle_close` – cleanup + `exit(0)` for the red cross event (event 17)
- [ ] `move_player` – W/S along `dir`, A/D perpendicular; check `map[new_y][new_x] != '1'`
- [ ] `rotate_player` – 2-D rotation matrix on `dir` and `plane`

### Player initialisation (shared with Manuel)
- [ ] After `parse_map` sets `player.start_dir` + `pos_x/pos_y`, Mario's code
      sets `dir_x/y` and `plane_x/y` based on `start_dir` (N/S/E/W)

---

## Manuel – Parsing, Validation, Errors

### Milestone 1 · Arguments + file reading
**Files:** `src/parsing/parse_args.c` · `src/parsing/read_file.c`
- [ ] `check_args` – exactly 2 args, extension must be `.cub`
- [ ] `read_cub_file` – open, `get_next_line` loop, NULL-terminated array
- [ ] Handle empty file (`ERR_EMPTY`) and `open` failure (`ERR_OPEN`)

### Milestone 2 · Texture paths
**File:** `src/parsing/parse_textures.c`
- [ ] Scan header lines for `NO` / `SO` / `WE` / `EA`
- [ ] Extract path after identifier + spaces
- [ ] Reject duplicates; verify all 4 are set at the end
- [ ] `ft_strdup` path into `tex->no_path / so_path / we_path / ea_path`

### Milestone 3 · Colors
**File:** `src/parsing/parse_colors.c`
- [ ] Parse `F R,G,B` and `C R,G,B` (identifiers can be in any order)
- [ ] Split by comma, `ft_atoi` each component
- [ ] Validate exactly 3 components and each in `[0, 255]`
- [ ] Reject duplicates; verify both F and C are set

### Milestone 4 · Map parsing
**File:** `src/parsing/parse_map.c`
- [ ] Detect map start (first line of `1`s / spaces after header)
- [ ] Subject rule: map is **always last** in the file
- [ ] Copy lines preserving spaces (`ft_strdup` each row)
- [ ] Compute `map->rows` and `map->cols` (pad short rows with spaces)
- [ ] Valid chars: `0` `1` ` ` `N` `S` `E` `W` – reject anything else
- [ ] Find player char → `player->start_dir` + `pos_x` + `pos_y`
- [ ] Exactly one player required (`ERR_PLAYER`)
- [ ] Replace player char with `'0'` on the grid

### Milestone 5 · Map closure validation
**File:** `src/parsing/validate_map.c`
- [ ] Flood-fill (BFS/DFS) from map borders
- [ ] If any reachable `0` or player cell is found → `ERR_MAP_CLOSED`
- [ ] Treat spaces as void/outside (reachable from border = open map)
- [ ] Free working copy after validation

### Milestone 6 · Error output
**File:** `src/utils/error.c`
- [ ] `print_error(msg)` – writes `"Error\n"` + msg to fd 2, returns 1
- [ ] `exit_error(game, msg)` – print + cleanup + `exit(1)`

---

## Shared tasks

### Structs (agree before coding)
All structs live in `includes/cub3d.h`:
- `t_color` · `t_img` · `t_tex` · `t_textures`
- `t_map` · `t_player` · `t_ray` · `t_mlx` · `t_game`
> **Discuss** before adding fields – both sides depend on these.

### Makefile
**File:** `Makefile`
- [ ] `all` `clean` `fclean` `re` rules
- [ ] `-Wall -Wextra -Werror` always
- [ ] No unnecessary relinking (use `.o` dependencies)
- [ ] Link with `-lm` and platform MLX flags

### libft + miniLibX
- [ ] Drop your `libft/` directory into the project root
- [ ] Drop the miniLibX `mlx/` directory into the project root
- [ ] Both are built by the Makefile automatically

### Test maps (already created in `maps/`)
| File | Purpose |
|---|---|
| `valid_simple.cub` | Basic smoke test |
| `valid_complex.cub` | Complex irregular map from subject |
| `invalid_open.cub` | Must print `Error\n` – map not closed |
| `invalid_color.cub` | Must print `Error\n` – RGB out of range |
| `invalid_missing_tex.cub` | Must print `Error\n` – EA missing |

---

## Branches

| Branch | Owner | Content |
|---|---|---|
| `main` | shared | reviewed + tested code only |
| `mario` | Mario | rendering, raycasting, events |
| `manuel` | Manuel | parsing, validation, errors |

```sh
git switch mario   # Mario works here
git switch manuel  # Manuel works here
# merge into main only after both compile + test
```

---

## Milestones order

```
M1: Arguments + file reading (Manuel) + MLX window (Mario)
M2: Color parsing (Manuel) + floor/ceiling render (Mario)
M3: Texture + map parsing (Manuel) + DDA raycasting (Mario)
M4: Map validation (Manuel) + textured walls (Mario)
M5: Error polish (Manuel) + movement/collision (Mario)
M6: Norm + leaks + defence tests (shared)
```

---

## Responsibility table

| Area | Main | Reviewer |
|---|---|---|
| Argument validation | Manuel | Mario |
| File reading | Manuel | Mario |
| Texture parsing (NO/SO/WE/EA) | Manuel | Mario |
| Color parsing (F/C) | Manuel | Mario |
| Map parsing | Manuel | Mario |
| Map closure validation | Manuel | Mario |
| Error output (`Error\n`) | Manuel | Mario |
| MLX init + image buffer | Mario | Manuel |
| Load XPM textures | Mario | Manuel |
| Raycasting / DDA | Mario | Manuel |
| Draw background | Mario | Manuel |
| Draw textured walls | Mario | Manuel |
| Movement + rotation | Mario | Manuel |
| Event hooks (ESC / close) | Mario | Manuel |
| Cleanup / free | shared | shared |
| Makefile | shared | shared |
| Test maps | shared | shared |
| Norm + leaks | shared | shared |
