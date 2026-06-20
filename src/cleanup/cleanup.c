/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/20 12:23:26 by mamarin-         ###   ########.fr       */
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

void	free_copy_map(char **copy)
{
	int i;

	i = 0;
	if (!copy)
		return ;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

/*
** free_textures – destroys MLX images for all 4 loaded textures.
*/
void	free_textures(t_game *game)
{
	if (game->tex.no.texture)
		mlx_delete_texture(game->tex.no.texture);
	if (game->tex.so.texture)
		mlx_delete_texture(game->tex.so.texture);
	if (game->tex.we.texture)
		mlx_delete_texture(game->tex.we.texture);
	if (game->tex.ea.texture)
		mlx_delete_texture(game->tex.ea.texture);
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
		mlx_delete_image(game->mlx.mlx, game->mlx.img.img);
	if (game->mlx.mlx)
		mlx_terminate(game->mlx.mlx);
}
