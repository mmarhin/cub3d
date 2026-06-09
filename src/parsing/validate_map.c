/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/09 14:07:33 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** validate_map
**
** Subject: the map must be closed/surrounded by walls.
**          Spaces count as outside/void – any '0' or player cell
**          reachable from an open border is an error.
**
** Strategy: flood-fill from every border-adjacent '0' or space.
**           If the fill reaches a '0' (walkable cell), the map is open.
**
** Returns 0 if valid, 1 + Error\n if the map is not properly closed.
*/

char **copy_map(t_map *map)
{
    int i;
    char **copy;
    
    i = 0;
    copy = NULL;
    while (map->grid[i])
        i++;
    copy = malloc(sizeof(t_map) * (i + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (map->grid[i])
    {
        copy[i] = ft_strdup(map->grid[i]);
        if (!copy[i])
            return (NULL);
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

static int	flood_fill(char **map, int x, int y, int rows, int cols)
{
    if (y < 0 || y >= rows || x < 0 || x >= cols)
        return (1);                  
    if (map[y][x] == '1' || map[y][x] == 'V')
        return (0);                 
    if (map[y][x] == ' ' || map[y][x] == '\0')
        return (1);                  
    map[y][x] = 'V';                 
    if (flood_fill(map, x + 1, y, rows, cols))
        return (1);
    if (flood_fill(map, x - 1, y, rows, cols))
        return (1);
    if (flood_fill(map, x, y + 1, rows, cols))
        return (1);
    if (flood_fill(map, x, y - 1, rows, cols))
        return (1);
    return (0);
}
    
static int	check_visited(char **copy, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (copy[i][j] == 'V')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	flood_fill_borders(char **copy, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (i == 0 || i == map->rows - 1
				|| j == 0 || j == map->cols - 1)
				if (copy[i][j] != '1')
					flood_fill(copy, j, i, map->rows, map->cols);
			j++;
		}
		i++;
	}
}

int	validate_map(t_map *map, t_player *player)
{
	char	**copy;

	(void)player;
	copy = copy_map(map);
	if (!copy)
		return (1);
	flood_fill_borders(copy, map);
	if (check_visited(copy, map))
	{
		free_copy_map(copy);
		return (print_error(ERR_MAP_CLOSED), 1);
	}
	free_copy_map(copy);
	return (0);
}
