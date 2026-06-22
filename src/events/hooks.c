/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/22 12:45:55 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** handle_keydown
**
** Subject requirements for controls:
**   KEY_ESC        → close window and quit cleanly
**   KEY_LEFT/RIGHT → rotate the camera (look left/right)
**   KEY_W/A/S/D    → move through the maze
*/
static void	handle_movement(t_game *game, bool *moved)
{
	if (mlx_is_key_down(game->mlx.mlx, KEY_W))
		(move_player(game, KEY_W), *moved = true);
	if (mlx_is_key_down(game->mlx.mlx, KEY_S))
		(move_player(game, KEY_S), *moved = true);
	if (mlx_is_key_down(game->mlx.mlx, KEY_A))
		(move_player(game, KEY_A), *moved = true);
	if (mlx_is_key_down(game->mlx.mlx, KEY_D))
		(move_player(game, KEY_D), *moved = true);
}

void	handle_loop(void *param)
{
	t_game	*game;
	bool	moved;

	game = param;
	moved = false;
	if (mlx_is_key_down(game->mlx.mlx, KEY_ESC))
		handle_close(param);
	if (mlx_is_key_down(game->mlx.mlx, KEY_LEFT))
		(rotate_player(game, KEY_LEFT), moved = true);
	if (mlx_is_key_down(game->mlx.mlx, KEY_RIGHT))
		(rotate_player(game, KEY_RIGHT), moved = true);
	handle_movement(game, &moved);
	if (moved)
		render_frame(game);
}

/*
** handle_close
**
** Subject: clicking the red cross on the window frame must close
**          the window and quit the program cleanly.
**
** Frees all resources and exits with code 0.
*/
void	handle_close(void *param)
{
	t_game	*game;

	game = param;
	cleanup_game(game);
	exit(0);
}
