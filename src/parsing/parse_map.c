/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** parse_map
**
** Subject rules for the map section:
**   - Map is ALWAYS the last section of the .cub file.
**   - Valid characters: '0' (empty), '1' (wall), ' ' (void/outside),
**     'N', 'S', 'E', 'W' (player start – exactly one required).
**   - Spaces are valid inside the map and must be preserved as-is.
**   - The map must be closed/surrounded by walls.
**   - Player start position sets pos_x/pos_y and start_dir on t_player.
**
** Returns 0 on success, 1 on any misconfiguration.
*/
int	parse_map(t_map *map, t_player *player, char **lines)
{
	/* TODO (Manuel):
	**   1. Find the first line that looks like a map line
	**      (starts with '1' or ' ', after all header elements are done).
	**   2. Copy those lines into map->grid (preserve spaces, strip '\n').
	**   3. Compute map->rows and map->cols (pad shorter rows with spaces).
	**   4. Validate every character: only '0','1',' ','N','S','E','W' allowed.
	**   5. Find and count player chars (N/S/E/W).
	**      - Exactly 1 required → store in player->start_dir + pos_x/pos_y.
	**      - Replace it with '0' on the grid after storing.
	**   6. Return 1 + print_error(...) on any violation.
	*/
	(void)map;
	(void)player;
	(void)lines;
	return (0);
}
