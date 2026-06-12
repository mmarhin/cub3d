/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 10:30:03 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/12 16:13:51 by mruiz-ur         ###   ########.fr       */
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

int	build_map_grid(char **lines, t_map *map)
{
	int		start;
	int		end;
	int		i;
	size_t	len;

	start = 0;
	end = -1;
	i = 0;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
			end = i;
		i++;
	}
	if (end < 0)
		return (print_error(ERR_MAP_CHAR), 1);
	start = end;
	while (start > 0 && !is_empty_line(lines[start - 1]))
		start--;
	map->rows = end - start + 1;
	map->cols = 0;
	map->grid = ft_calloc(map->rows + 1, sizeof(char *));
	if (!map->grid)
		return (1);
	i = 0;
	while (i < map->rows)
	{
		len = ft_strlen(lines[start + i]);
		if (len > 0 && lines[start + i][len - 1] == '\n')
			len--;
		if ((int)len > map->cols)
			map->cols = len;
		map->grid[i] = ft_substr(lines[start + i], 0, len);
		if (!map->grid[i])
			return (1);
		i++;
	}
	return (0);
}

