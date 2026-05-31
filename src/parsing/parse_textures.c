/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** parse_textures
**
** Subject: each texture identifier (NO / SO / WE / EA) must appear
**          exactly once, followed by the path to the texture.
**          Order among identifiers is free.
**          Identifiers can be separated from the map by empty lines.
**
** Returns 0 on success, 1 on any misconfiguration.
*/
int	parse_textures(t_textures *tex, char **lines)
{
	/* TODO (Manuel):
	**   1. Iterate over lines[] until the map starts.
	**   2. For each line that starts with NO/SO/WE/EA:
	**      a. Check it has not already been set (duplicate check).
	**      b. Extract the path (everything after the identifier + spaces).
	**      c. Duplicate the path into tex->no_path / so_path / we_path / ea_path.
	**   3. After scanning all header lines, verify all 4 paths are set.
	**   4. Return 1 + print_error(ERR_TEX) on any failure.
	*/
	(void)tex;
	(void)lines;
	return (0);
}
