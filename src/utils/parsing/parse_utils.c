/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 10:30:03 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/22 12:30:49 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

static int	find_boundaries(char **lines, int *start, int *end)
{
	int	i;

	*end = -1;
	i = 0;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
			*end = i;
		i++;
	}
	if (*end < 0)
		return (print_error(ERR_MAP_CHAR), 1);
	*start = *end;
	while (*start > 0 && !is_empty_line(lines[*start - 1]))
		(*start)--;
	return (0);
}

static size_t	trimmed_len(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	return (len);
}

static int	build_map(t_map *map, char **lines, int *start, size_t len)
{
	int		i;
	size_t	j;

	i = -1;
	while (++i < map->rows)
	{
		len = trimmed_len(lines[*start + i]);
		map->grid[i] = ft_calloc(map->cols + 1, sizeof(char));
		if (!map->grid[i])
			return (1);
		ft_memset(map->grid[i], ' ', map->cols);
		j = 0;
		while (j < len)
		{
			map->grid[i][j] = lines[*start + i][j];
			j++;
		}
	}
	return (0);
}

int	build_map_grid(char **lines, t_map *map)
{
	int		start;
	int		end;
	int		i;
	size_t	len;

	if (find_boundaries(lines, &start, &end))
		return (1);
	map->rows = end - start + 1;
	map->cols = 0;
	i = -1;
	while (++i < map->rows)
	{
		len = trimmed_len(lines[start + i]);
		if ((int)len > map->cols)
			map->cols = len;
	}
	map->grid = ft_calloc(map->rows + 1, sizeof(char *));
	if (!map->grid)
		return (1);
	if (build_map(map, lines, &start, len) == 1)
		return (1);
	return (0);
}
