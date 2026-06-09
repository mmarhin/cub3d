/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/09 15:56:47 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../Libft/libft.h"
# include "MLX42/MLX42.h"

/* -- Window ---------------------------------------------------------------- */
# define WIN_W		1280
# define WIN_H		720
# define WIN_TITLE	"cub3D"

/* -- Movement / rotation speeds ------------------------------------------- */
# define MOVE_SPEED	0.05
# define ROT_SPEED	0.03

/* -- MLX keycodes ---------------------------------------------------------- */
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_ESC	65307

/* -- Subject-required map chars -------------------------------------------- */
# define EMPTY		'0'
# define WALL		'1'
/* player start chars: 'N' 'S' 'E' 'W' (handled in parsing) */

/* -- Error messages -------------------------------------------------------- */
# define ERR_ARGS	"Usage: ./cub3D <scene.cub>\n"
# define ERR_EXT	"Scene file must have a .cub extension\n"
# define ERR_OPEN	"Cannot open scene file\n"
# define ERR_EMPTY	"Scene file is empty\n"
# define ERR_TEX	"Missing or duplicate texture identifier (NO/SO/WE/EA)\n"
# define ERR_COLOR	"Invalid floor or ceiling color (F/C must be R,G,B in 0-255)\n"
# define ERR_MAP_CHAR	"Invalid character in map\n"
# define ERR_MAP_CLOSED	"Map is not closed/surrounded by walls\n"
# define ERR_PLAYER	"Map must have exactly one player start position (N/S/E/W)\n"
# define ERR_MLX	"MLX initialization failed\n"
# define ERR_TEX_LOAD	"Failed to load texture\n"

/* -------------------------------------------------------------------------- */
/*  Data structures                                                            */
/* -------------------------------------------------------------------------- */

/* RGB color – used for floor (F) and ceiling (C) */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* MLX render image */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/* One XPM wall texture */
typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

/*
** Four directional textures required by the subject:
**   NO – North wall
**   SO – South wall
**   WE – West wall
**   EA – East wall
*/
typedef struct s_textures
{
	t_tex	no;
	t_tex	so;
	t_tex	we;
	t_tex	ea;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}	t_textures;

/* Map grid parsed from the .cub file */
typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;		/* max column width (padded with spaces) */
}	t_map;

/*
** Player state – position + direction vector + camera plane.
** start_dir stores the char found on the map: N / S / E / W
*/
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;	/* camera plane for FOV */
	double	plane_y;
	char	start_dir;
}	t_player;

/* Per-column ray data computed during raycasting */
typedef struct s_ray
{
	double	camera_x;		/* x in camera space [-1, 1] */
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;	/* avoids fisheye */
	int		step_x;
	int		step_y;
	int		hit;			/* 1 when DDA hits a wall */
	int		side;			/* 0 = X side hit, 1 = Y side hit */
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;			/* X coordinate inside the texture */
}	t_ray;

/* MLX window / image context */
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

/* Master game struct – passed everywhere */
typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_textures	tex;
	t_color		floor;
	t_color		ceiling;
}	t_game;

/* -------------------------------------------------------------------------- */
/*  Prototypes                                                                 */
/* -------------------------------------------------------------------------- */

/* --- Parsing (Manuel) --- */
/* src/parsing/parse_args.c */
int		check_args(int argc, char **argv);

/* src/parsing/read_file.c */
char	**read_cub_file(char *path);

/* src/parsing/parse_textures.c */
int		parse_textures(t_textures *tex, char **lines);

/* src/parsing/parse_colors.c */
int		parse_colors(t_color *floor, t_color *ceiling, char **lines);

/* src/parsing/parse_map.c */
int		parse_map(t_map *map, t_player *player);
int		build_map_grid(char **lines, t_map *map);
int		is_empty_line(char *line);


/* src/parsing/validate_map.c */
int		validate_map(t_map *map, t_player *player);

/* --- Rendering (Mario) --- */
/* src/rendering/init_mlx.c */
int		init_mlx(t_game *game);

/* src/rendering/load_textures.c */
int		load_textures(t_game *game);

/* src/rendering/raycasting.c */
void	cast_rays(t_game *game);

/* src/rendering/draw.c */
void	draw_background(t_game *game);
void	draw_wall_slice(t_game *game, int col, t_ray *ray);
void	render_frame(t_game *game);

/* src/rendering/texture_utils.c */
int		get_tex_color(t_tex *tex, int x, int y);
void	calc_tex_x(t_game *game, t_ray *ray);

/* --- Events (Mario) --- */
/* src/events/hooks.c */

// int handle_keydown(int keycode, void *param);

void 	handle_keydown(mlx_key_data_t keydata, void *param);
void 	handle_close(void *param);
// int		handle_close(t_game *game);

/* src/events/move.c */
void	move_player(t_game *game, int keycode);
void	rotate_player(t_game *game, int keycode);

/* --- Cleanup (shared) --- */
/* src/cleanup/cleanup.c */
void	free_map(t_map *map);
void	free_copy_map(char **copy);
void	free_textures(t_game *game);
void	free_lines(char **lines);
void	cleanup_game(t_game *game);

/* --- Error utils (Manuel) --- */
/* src/utils/error.c */
int		print_error(char *msg);
void	exit_error(t_game *game, char *msg);

#endif
