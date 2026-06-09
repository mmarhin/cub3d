/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/09 14:41:41 by mruiz-ur         ###   ########.fr       */
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
void	handle_keydown(mlx_key_data_t keydata, void *param)
{
	t_game	*game = param;

	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	if (keydata.key == KEY_ESC)
		handle_close(param);
	else if (keydata.key == KEY_LEFT || keydata.key == KEY_RIGHT)
		rotate_player(game, keydata.key);
	else if (keydata.key == KEY_W || keydata.key == KEY_A
		|| keydata.key == KEY_S || keydata.key == KEY_D)
		move_player(game, keydata.key);
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
	t_game	*game = param;

	cleanup_game(game);
	exit(0);
}
