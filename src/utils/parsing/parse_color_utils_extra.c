/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils_extra.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:27:01 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/09/14 11:27:24 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_duplicated(char c, t_color *floor,
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
