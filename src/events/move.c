/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** move_player
**
** Subject: W, A, S, D keys move the point of view through the maze.
**          Wall collision must be handled (player cannot walk through walls).
**
** Movement is along the player direction vector (W/S) or the
** perpendicular strafe vector (A/D).
*/
void	move_player(t_game *game, int keycode)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &game->player;
	/* TODO (Mario):
	**   For W: new_x = pos_x + dir_x * MOVE_SPEED
	**          new_y = pos_y + dir_y * MOVE_SPEED
	**   For S: subtract instead.
	**   For A: strafe left (perpendicular to dir).
	**   For D: strafe right.
	**   Collision: only update pos_x if map[map_y][(int)new_x] != '1'
	**              only update pos_y if map[(int)new_y][map_x] != '1'
	*/
	(void)p;
	(void)new_x;
	(void)new_y;
	(void)keycode;
	(void)game;
}

/*
** rotate_player
**
** Subject: left and right arrow keys rotate the view (camera).
**
** Uses a 2D rotation matrix on the direction vector and camera plane:
**   new_dir_x = dir_x * cos(±ROT_SPEED) - dir_y * sin(±ROT_SPEED)
**   new_dir_y = dir_x * sin(±ROT_SPEED) + dir_y * cos(±ROT_SPEED)
** Same rotation applied to plane_x / plane_y.
*/
void	rotate_player(t_game *game, int keycode)
{
	/* TODO (Mario):
	**   Pick angle: KEY_LEFT → +ROT_SPEED, KEY_RIGHT → -ROT_SPEED
	**   Apply rotation matrix to game->player.dir_x/dir_y
	**   Apply same rotation to game->player.plane_x/plane_y
	*/
	(void)game;
	(void)keycode;
}
