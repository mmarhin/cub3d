/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/02 11:36:17 by mruiz-ur         ###   ########.fr       */
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
char	**read_cub_file(char *path)
{
	/* TODO (Manuel):
	**   1. open(path, O_RDONLY) – return NULL on failure
	**   2. Read all lines with get_next_line
	**   3. Store in a dynamically grown array
	**   4. Close fd and return the array
	**   5. Return NULL + print_error(ERR_EMPTY) if file has no lines
	*/
	int	fd;
    char	*line;
    char    **map;
    int	count;
	
	count = 0;
	map = NULL;
	if (!path)
		return (NULL);
	fd = open(path, 0_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		map = realloc(map, sizeof(char *) * (count + 2));
		if (!map)
			return (NULL);
		map[count] = strdup(line);
		map[count++];
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!map)
		return (print_error(ERR_EMPTY), NULL);
	return (map);
}
