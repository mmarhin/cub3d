/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/28 13:14:58 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// static int	is_open_side(char **grid, t_map *map, int y, int x)
// {
// 	int	len;

// 	if (y < 0 || y >= map->rows)
// 		return (1);
// 	len = ft_strlen(grid[y]);
// 	if (x < 0 || x >= len)
// 		return (1);
// 	if (grid[y][x] == ' ' || grid[y][x] == '\0')
// 		return (1);
// 	return (0);
// }

// static int	cell_is_open(char **grid, t_map *map, int y, int x)
// {
// 	if (grid[y][x] != '0')
// 		return (0);
// 	if (is_open_side(grid, map, y - 1, x)
// 		|| is_open_side(grid, map, y + 1, x)
// 		|| is_open_side(grid, map, y, x - 1)
// 		|| is_open_side(grid, map, y, x + 1))
// 		return (1);
// 	return (0);
// }

// static int	validate_cells(char **grid, t_map *map)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < map->rows)
// 	{
// 		x = 0;
// 		while (x < map->cols)
// 		{
// 			if (cell_is_open(grid, map, y, x))
// 				return (1);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }

// int	validate_map(t_map *map, t_player *player)
// {
// 	(void)player;
// 	if (!map || !map->grid || map->rows <= 0 || map->cols <= 0)
// 		return (print_error(ERR_MAP_CLOSED), 1);
// 	if (validate_cells(map->grid, map))
// 		return (print_error(ERR_MAP_CLOSED), 1);
// 	return (0);
// }

static void	free_grid(char **copy)
{
	int i;

	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

static char	**copy_grid(char **grid, int rows)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
		{
			free_grid(copy);
			return (NULL);
		}
		i++;
	}
	copy[rows] = NULL;
	return (copy);
}

static int	flood_fill(char **grid, t_map *map, int y, int x)
{
	if (y < 0 || y >= map->rows)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(grid[y]))
		return (1);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (0);	
	grid[y][x] = 'V'; // marcamos como visitado
	if (flood_fill(grid, map, y - 1, x))
		return (1);
	if (flood_fill(grid, map, y + 1, x))
		return (1);
	if (flood_fill(grid, map, y, x - 1))
		return (1);
	if (flood_fill(grid, map, y, x + 1))
		return (1);
	return (0);
}

int	validate_map(t_map *map, t_player *player)
{
	char	**grid_copy;
	int		result;

	if (!map || !map->grid || map->rows <= 0 || map->cols <= 0)
		return (print_error(ERR_MAP_CLOSED), 1);

	grid_copy = copy_grid(map->grid, map->rows);
	if (!grid_copy)
		return (1);

	result = flood_fill(grid_copy, map, player->pos_y, player->pos_x);
	free_grid(grid_copy);

	if (result)
		return (print_error(ERR_MAP_CLOSED), 1);
	return (0);
}