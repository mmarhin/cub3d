/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** parse_colors
**
** Subject: F and C identifiers define floor and ceiling colors.
**          Format: F R,G,B  /  C R,G,B
**          Each component must be in range [0, 255].
**          Identifiers can be in any order among header lines.
**
** Returns 0 on success, 1 on any misconfiguration.
*/
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
	(void)floor;
	(void)ceiling;
	(void)lines;
	return (0);
}
