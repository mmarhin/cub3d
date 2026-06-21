/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/20 12:23:26 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** read_cub_file
**
** Opens the .cub file and returns its lines as a NULL-terminated
** array of strings (one entry per line, newlines stripped).
**
** Subject notes:
**   - Elements can be separated by one or more empty lines.
**   - Map content must always be last.
**   - Spaces inside the map are valid and must be preserved.
**
** Returns NULL and prints Error\n on failure.
*/

static int	init_vars(char *path, int *count, char ***map, int *fd)
{
	*count = 0;
	*map = NULL;
	if (!path)
		return (1);
	*fd = open(path, O_RDONLY);
	return (0);
}

static char	**realloc_lines(char **old_map, int count)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	if (old_map)
	{
		while (i < count)
		{
			new_map[i] = old_map[i];
			i++;
		}
		free(old_map);
	}
	new_map[i] = NULL;
	new_map[i + 1] = NULL;
	return (new_map);
}

static int	add_line_to_map(char ***map, char *line, int *count)
{
	char	**new_map;

	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	new_map = realloc_lines(*map, *count);
	if (!new_map)
		return (1);
	*map = new_map;
	(*map)[*count] = ft_strdup(line);
	if (!(*map)[*count])
		return (1);
	(*map)[*count + 1] = NULL;
	(*count)++;
	return (0);
}

char	**read_cub_file(char *path)
{
	int		fd;
	char	*line;
	char	**map;
	int		count;

	if (init_vars(path, &count, &map, &fd) || fd == -1)
		return (print_error(ERR_OPEN), NULL);
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		if (add_line_to_map(&map, line, &count))
		{
			free(line);
			free_lines(map);
			close(fd);
			return (NULL);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (!map)
		return (print_error(ERR_EMPTY), NULL);
	return (map);
}
