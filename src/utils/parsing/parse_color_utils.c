/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:58:35 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/28 11:32:09 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	assign_floor_color(t_color *floor, int r, int g, int b)
{
	floor->r = r;
	floor->g = g;
	floor->b = b;
}

void	assign_ceiling_color(t_color *ceiling, int r, int g, int b)
{
	ceiling->r = r;
	ceiling->g = g;
	ceiling->b = b;
}

int	check_if_trim(int len, char *content)
{
    if (len == 0 || content[len - 1] == ',')
	{
        return (1);
	}
	return (0);
}

int	check_exact_parts(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (1);
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (rgb[i][j] == ' ' || rgb[i][j] == '\t')
				j++;
			if (!ft_isdigit(rgb[i][j]))
				return (1);
			j++;
		}
		if (j == 0)
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

char *remove_spaces(char *s)
{
	int i;
	int j;
	char *result; 
	
	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * ft_strlen(s) + 1);
	if (!result)
		return (free(result), NULL);
	while (s[i])
	{
		if (s[i] != ' ')
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	return (result);	
}
