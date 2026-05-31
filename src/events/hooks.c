/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
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
int	handle_keydown(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_player(game, keycode);
	else if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
		move_player(game, keycode);
	render_frame(game);
	return (0);
}

/*
** handle_close
**
** Subject: clicking the red cross on the window frame must close
**          the window and quit the program cleanly.
**
** Frees all resources and exits with code 0.
*/
int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
