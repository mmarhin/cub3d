/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/20 12:23:26 by mamarin-         ###   ########.fr       */
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
	game->mlx.mlx = mlx_init(WIN_W, WIN_H, WIN_TITLE, false);
	if (!game->mlx.mlx)
		return (print_error(ERR_MLX), 1);
	game->mlx.img.img = mlx_new_image(game->mlx.mlx, WIN_W, WIN_H);
	if (!game->mlx.img.img)
	{
		mlx_terminate(game->mlx.mlx);
		game->mlx.mlx = NULL;
		return (print_error(ERR_MLX), 1);
	}
	return (0);
}
