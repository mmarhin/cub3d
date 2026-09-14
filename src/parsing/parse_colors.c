/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/28 11:34:22 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int  rgb_split(int id, char *content, t_color *ceiling, t_color *floor)
{
    char    **rgb;
    int     len;
    int     col[3];

	len = ft_strlen(content);
    if (id != 1 && id != 2)
        return (1);
    if (check_if_trim(len, content))
        return (1);
    rgb = ft_split(content, ',');
    if (!rgb || check_exact_parts(rgb))
        return (!rgb ? 1 : (free_lines(rgb), 1));
    col[0] = ft_atoi(rgb[0]);
    col[1] = ft_atoi(rgb[1]);
    col[2] = ft_atoi(rgb[2]);
    if (col[0] < 0 || col[0] > 255 || col[1] < 0 || col[1] > 255
        || col[2] < 0 || col[2] > 255)
        return (free_lines(rgb), 1);
    if (id == 1)
        assign_floor_color(floor, col[0], col[1], col[2]);
    else
        assign_ceiling_color(ceiling, col[0], col[1], col[2]);
    free_lines(rgb);
    return (0);
}

 
static char	*extract_color_content(char *line)
{
	int	start;
	int	len;
	char	*result;
	char	*substr;

	start = 1;
	while (line[start] == ' ')
		start++;
	if (line[start] == '\0')
		return (NULL);
	len = 0;
	while (line[start + len] && line[start + len] != '\t' && line[start + len] != '\n')
		len++;
	if (len == 0)
		return (NULL);
	substr = ft_substr(line, start, len);
	if (!substr)
		return (NULL);
	result = remove_spaces(substr);
	free(substr);
	if (!result)
		return (NULL);
	return (result);
}

static void	init_vars(t_color *floor, t_color *ceiling, int *i, int *id)
{
	floor->r = -1;
	ceiling->r = -1;
	*i = 0;
	*id = 0;
}

static int	check_if_duplicated(char c, t_color *floor,
				t_color *ceiling, int *id)
{
	if (c == 'F')
	{
		if (floor->r != -1)
			return (1);
		*id = 1;
	}
	else
	{
		if (ceiling->r != -1)
			return (1);
		*id = 2;
	}
	return (0);
}

int	parse_colors(t_color *floor, t_color *ceiling, char **lines)
{
	int		i;
	int		id;
	char	*content;

	init_vars(floor, ceiling, &i, &id);
	while (lines[i])
	{
		if (lines[i][0] == 'F' || lines[i][0] == 'C')
		{
			content = extract_color_content(lines[i]);
			if (!content)
				return (free(content), print_error(ERR_COLOR), 1);
			if (check_if_duplicated(lines[i][0], floor, ceiling, &id)
				|| !content)
				return (print_error(ERR_COLOR), 1);
			if (rgb_split(id, content, ceiling, floor))
				return (free(content), print_error(ERR_COLOR), 1);
			free(content);
		}
		i++;
	}
	if (floor->r == -1 || ceiling->r == -1)
		return (print_error(ERR_COLOR), 1);
	return (0);
}
