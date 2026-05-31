/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** validate_map
**
** Subject: the map must be closed/surrounded by walls.
**          Spaces count as outside/void – any '0' or player cell
**          reachable from an open border is an error.
**
** Strategy: flood-fill from every border-adjacent '0' or space.
**           If the fill reaches a '0' (walkable cell), the map is open.
**
** Returns 0 if valid, 1 + Error\n if the map is not properly closed.
*/
int	validate_map(t_map *map)
{
	/* TODO (Manuel):
	**   1. Make a working copy of map->grid.
	**   2. Run a flood-fill (BFS or DFS) from every edge cell that
	**      is '0', 'N', 'S', 'E', 'W', or ' '.
	**   3. If the fill can reach a walkable cell without crossing a '1',
	**      the map is open → return 1 + print_error(ERR_MAP_CLOSED).
	**   4. Free the working copy and return 0 on success.
	*/
	(void)map;
	return (0);
}
