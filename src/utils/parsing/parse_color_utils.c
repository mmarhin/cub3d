/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:58:35 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/18 14:59:40 by mruiz-ur         ###   ########.fr       */
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

int	check_exact_parts(char **rgb)
{
	int	i;
	int	j;

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
