/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/18 14:51:33 by mruiz-ur         ###   ########.fr       */
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

static int init_vars(char *path, int *count, char ***map, int *fd)
{
	*count = 0;
	*map = NULL;
	if (!path)
		return (1);
	*fd = open(path, O_RDONLY);
	return (0);
}

static int add_line_to_map(char ***map, char *line, int *count)
{
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	*map = realloc(*map, sizeof(char *) * (*count + 2));
	if (!*map)
		return (1);
	(*map)[*count] = ft_strdup(line);
	(*map)[*count + 1] = NULL;
	(*count)++;
	return (0);
}

char	**read_cub_file(char *path)
{
	int	fd;
    char	*line;
    char    **map;
    int	count;
	
	if (init_vars(path, &count, &map, &fd) == 1)
		return (NULL);
	if (fd == -1)
		return (NULL);
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		if (add_line_to_map(&map, line, &count))
		{
			free(line);
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
