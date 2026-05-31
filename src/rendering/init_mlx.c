/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** init_mlx
**
** Subject: use miniLibX; window management must remain smooth
**          (resize, minimize, switch to another window, etc.).
**
** Creates the mlx connection, the window, and the render image buffer.
** Returns 0 on success, 1 on failure.
*/
int	init_mlx(t_game *game)
{
	/* TODO (Mario):
	**   1. game->mlx.mlx = mlx_init()         → check NULL
	**   2. game->mlx.win = mlx_new_window(...) → check NULL
	**   3. game->mlx.img.img = mlx_new_image(...)
	**   4. game->mlx.img.addr = mlx_get_data_addr(
	**          game->mlx.img.img,
	**          &game->mlx.img.bpp,
	**          &game->mlx.img.line_len,
	**          &game->mlx.img.endian)
	**   5. Return 0 on success, 1 + print_error(ERR_MLX) on failure.
	*/
	(void)game;
	return (0);
}
