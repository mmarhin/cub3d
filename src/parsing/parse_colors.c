/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/09 13:39:16 by mruiz-ur         ###   ########.fr       */
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

int	parse_colors(t_color *floor, t_color *ceiling, char **lines)
{
	/* TODO (Manuel):
	**   1. Iterate header lines (before the map).
	**   2. For lines starting with 'F' or 'C':
	**      a. Split the R,G,B part by commas.
	**      b. Convert each part with ft_atoi.
	**      c. Validate: exactly 3 components, each in [0,255].
	**      d. Check no duplicates.
	**   3. Verify both F and C have been set.
	**   4. Return 1 + print_error(ERR_COLOR) on any failure.
	*/
	
	int		i;
	int		j;
	int		id;
	char	*content;

	floor->r = -1;
	ceiling->r = -1;
	i = 0;
	while (lines[i])
	{
		j = 0;
		if (lines[i][j] == 'F' || lines[i][j] == 'C')
		{
			if (lines[i][j] == 'F')
			{
				if (floor->r != -1)
					return (print_error(ERR_COLOR), 1);
				id = 1;
			}
			else
			{
				if (ceiling->r != -1)
					return (print_error(ERR_COLOR), 1);
				id = 2;
			}
			content = extract_color_content(lines[i]);
			if (!content)
				return (print_error(ERR_COLOR), 1);
			if (rgb_split(id, content, ceiling, floor) == 1)
			{
				free(content);
				print_error(ERR_COLOR);
				return (1);
			}
			free(content);
		}
		i++;
	}
	if (floor->r == -1 || ceiling->r == -1)
	{
		print_error(ERR_COLOR);
		return (1);
	}	
	return (0);
}
