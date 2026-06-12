/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/12 14:24:52 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	assign_floor_color(t_color *floor, int r, int g, int b)
{
	floor->r = r;
	floor->g = g;
	floor->b = b;
}

static void	assign_ceiling_color(t_color *ceiling, int r, int g, int b)
{
	ceiling->r = r;
	ceiling->g = g;
	ceiling->b = b;
}

static int	check_exact_parts(char **rgb)
{
	int i;
	int j;

	i = 0;
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (1);
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

static int	rgb_split(int id, char *content, t_color *ceiling, t_color *floor)
{
	char **rgb;
	int r;
	int g;
	int b;

	if (id != 1 && id != 2)
		return (1);
	rgb = ft_split(content, ',');
	if (!rgb)
		return (1);
	if (check_exact_parts(rgb))
		return (free_lines(rgb), 1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_lines(rgb), 1);
	if (id == 1)
		assign_floor_color(floor, r, g, b);
	else
		assign_ceiling_color(ceiling, r, g, b);
	free_lines(rgb);
	return (0);
}

static char	*extract_color_content(char *line)
{
	int	start;
	int	len;

	start = 1;
	while (line[start] == ' ')
		start++;
	if (line[start] == '\0')
		return (NULL);
	len = 0;
	while (line[start + len] && line[start + len] != ' '
		&& line[start + len] != '\t' && line[start + len] != '\n')
		len++;
	if (len == 0)
		return (NULL);
	return (ft_substr(line, start, len));
}

static void	init_vars(t_color *floor, t_color *ceiling, int *i, int *id)
{
	floor->r = -1;
	ceiling->r = -1;
	*i = 0;
	*id = 0;
}

static int check_if_duplicated(char c, t_color *floor, t_color *ceiling, int *id)
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
            if (check_if_duplicated(lines[i][0], floor, ceiling, &id)
                || !(content = extract_color_content(lines[i])))
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
