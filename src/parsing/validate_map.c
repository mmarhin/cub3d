/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/20 12:23:26 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


static int	is_open_side(char **grid, t_map *map, int y, int x)
{
	int	len;

	if (y < 0 || y >= map->rows)
		return (1);
	len = ft_strlen(grid[y]);
	if (x < 0 || x >= len)
		return (1);
	if (grid[y][x] == ' ' || grid[y][x] == '\0')
		return (1);
	return (0);
}

static int	cell_is_open(char **grid, t_map *map, int y, int x)
{
	if (grid[y][x] != '0')
		return (0);
	if (is_open_side(grid, map, y - 1, x)
		|| is_open_side(grid, map, y + 1, x)
		|| is_open_side(grid, map, y, x - 1)
		|| is_open_side(grid, map, y, x + 1))
		return (1);
	return (0);
}

static int	validate_cells(char **grid, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (cell_is_open(grid, map, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map(t_map *map, t_player *player)
{
	(void)player;
	if (!map || !map->grid || map->rows <= 0 || map->cols <= 0)
		return (print_error(ERR_MAP_CLOSED), 1);
	if (validate_cells(map->grid, map))
		return (print_error(ERR_MAP_CLOSED), 1);
	return (0);
}
