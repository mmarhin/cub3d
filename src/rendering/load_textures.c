/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** load_textures
**
** Subject: display different wall textures that vary depending on
**          which side the wall is facing (North, South, East, West).
**
** Loads the 4 XPM textures whose paths were parsed by Manuel.
** Returns 0 on success, 1 on failure.
*/
int	load_textures(t_game *game)
{
	/* TODO (Mario):
	**   Load each of the 4 textures with mlx_xpm_file_to_image:
	**     game->tex.no / so / we / ea
	**   For each texture:
	**     1. Call mlx_xpm_file_to_image(mlx, path, &width, &height)
	**     2. Check for NULL → print_error(ERR_TEX_LOAD) + return 1
	**     3. Get data addr with mlx_get_data_addr (bpp, line_len, endian)
	**     4. Store width and height on the t_tex struct
	*/
	(void)game;
	return (0);
}
