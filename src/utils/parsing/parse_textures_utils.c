/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:01:27 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/23 14:36:40 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	save_path(char *path, t_textures *tex, char pos)
{
	if (pos == 'N')
		tex->no_path = path;
	else if (pos == 'S')
		tex->so_path = path;
	else if (pos == 'W')
		tex->we_path = path;
	else if (pos == 'E')
		tex->ea_path = path;
}

int	cardinate_exists(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'));
}

int	tex_line_fail(char *line, int start)
{
	return ((line[start] == 'N' && line[start + 1] == 'O')
		|| (line[start] == 'S' && line[start + 1] == 'O')
		|| (line[start] == 'W' && line[start + 1] == 'E')
		|| (line[start] == 'E' && line[start + 1] == 'A'));
}

//Find_boundaries part of function placed here for norminette
void	init_boundaries_vars(int *i, int *in_map, int *map_ended)
{
	*i = 0;
	*in_map = 0;
	*map_ended = 0;
}