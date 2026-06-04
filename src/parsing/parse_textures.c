/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/02 11:34:38 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** parse_textures
**
** Subject: each texture identifier (NO / SO / WE / EA) must appear
**          exactly once, followed by the path to the texture.
**          Order among identifiers is free.
**          Identifiers can be separated from the map by empty lines.
**
** Returns 0 on success, 1 on any misconfiguration.
*/

static void	save_path(char *path, t_textures *tex)
{
	if (!path)
		return (1);
	if (lines[i][j] == 'N')
		tex->no_path = path;
	else if (lines[i][j] == 'S')
		tex->so_path = path;
	else if (lines[i][j] == 'W')
		tex->we_path = path;
	else if (lines[i][j] == 'E')
		tex->ea_path = path;
}

static int cardinate_exists(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'));
}


static char	*extract_path(char *line)
{
	int		start;
	int		len;
	char	*path;

	if (!line)
		return (print_error(ERR_TEXT), NULL);
	start = 0;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	if (!((line[start] == 'N' && line[start + 1] == 'O')
			|| (line[start] == 'S' && line[start + 1] == 'O')
			|| (line[start] == 'W' && line[start + 1] == 'E')
			|| (line[start] == 'E' && line[start + 1] == 'A')))
		return (print_error(ERR_TEXT), NULL);
	start += 2;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	len = 0;
	while (line[start + len] && line[start + len] != ' '
		&& line[start + len] != '\t' && line[start + len] != '\n')
		len++;
	if (len == 0)
		return (print_error(ERR_TEXT), NULL);
	path = ft_substr(line, start, len);
	if (!path)
		return (print_error(ERR_TEXT), NULL);
	return (path);
}


static int	check_if_tex_duplicated(char **lines, int i, int j)
{
	static int	no_seen;
	static int	so_seen;
	static int	we_seen;
	static int	ea_seen;

	if (lines[i][j] == 'N' && lines[i][j + 1] == 'O' && no_seen)
		return (1);
	if (lines[i][j] == 'S' && lines[i][j + 1] == 'O' && so_seen)
		return (1);
	if (lines[i][j] == 'W' && lines[i][j + 1] == 'E' && we_seen)
		return (1);
	if (lines[i][j] == 'E' && lines[i][j + 1] == 'A' && ea_seen)
		return (1);
	if (lines[i][j] == 'N' && lines[i][j + 1] == 'O')
		no_seen = 1;
	else if (lines[i][j] == 'S' && lines[i][j + 1] == 'O')
		so_seen = 1;
	else if (lines[i][j] == 'W' && lines[i][j + 1] == 'E')
		we_seen = 1;
	else if (lines[i][j] == 'E' && lines[i][j + 1] == 'A')
		ea_seen = 1;
	return (0);
}


int	parse_textures(t_textures *tex, char **lines)
{
	int		i;
	int		j;
	int		count_tex;
	char	*path;

	if (!tex || !lines)
		return (print_error(ERR_TEXT));
	i = 0;
	count_tex = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ' || lines[i][j] == '\t')
			j++;
		if (cardinate_exists(lines[i] + j))
		{
			if (check_if_tex_duplicated(lines, i, j) == 1)
				return (print_error(ERR_TEXT));
			path = extract_path(lines[i]);
			save_path(path, tex);
			count_tex++;
		}
		i++;
	}
	if (count_tex != 4 || !tex->no_path || !tex->so_path
		|| !tex->we_path || !tex->ea_path)
		return (print_error(ERR_TEXT));
	return (0);
}
