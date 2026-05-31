/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** free_lines – frees a NULL-terminated array of strings.
*/
void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

/*
** free_map – frees the 2D map grid.
*/
void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->rows)
		free(map->grid[i++]);
	free(map->grid);
	map->grid = NULL;
}

/*
** free_textures – destroys MLX images for all 4 loaded textures.
*/
void	free_textures(t_game *game)
{
	void	*mlx;

	mlx = game->mlx.mlx;
	if (!mlx)
		return ;
	if (game->tex.no.img)
		mlx_destroy_image(mlx, game->tex.no.img);
	if (game->tex.so.img)
		mlx_destroy_image(mlx, game->tex.so.img);
	if (game->tex.we.img)
		mlx_destroy_image(mlx, game->tex.we.img);
	if (game->tex.ea.img)
		mlx_destroy_image(mlx, game->tex.ea.img);
	free(game->tex.no_path);
	free(game->tex.so_path);
	free(game->tex.we_path);
	free(game->tex.ea_path);
}

/*
** cleanup_game
**
** Subject: frees all memory and destroys the window on exit.
**          Called on clean exit (ESC / red cross) and on errors.
*/
void	cleanup_game(t_game *game)
{
	free_textures(game);
	free_map(&game->map);
	if (game->mlx.img.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	if (game->mlx.mlx)
		mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
}
