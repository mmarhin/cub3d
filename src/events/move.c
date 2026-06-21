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
**
** TODO (Mario):
**   For W: new_x = pos_x + dir_x * MOVE_SPEED
**          new_y = pos_y + dir_y * MOVE_SPEED
**   For S: subtract instead.
**   For A: strafe left (perpendicular to dir).
**   For D: strafe right.
**   Collision: only update pos_x if map[map_y][(int)new_x] != '1'
**              only update pos_y if map[(int)new_y][map_x] != '1'
*/
static void	calc_new_pos(t_player *p, int keycode, double *nx, double *ny)
{
	if (keycode == KEY_W)
	{
		*nx += p->dir_x * MOVE_SPEED;
		*ny += p->dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_S)
	{
		*nx -= p->dir_x * MOVE_SPEED;
		*ny -= p->dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_D)
	{
		*nx += p->plane_x * MOVE_SPEED;
		*ny += p->plane_y * MOVE_SPEED;
	}
	else if (keycode == KEY_A)
	{
		*nx -= p->plane_x * MOVE_SPEED;
		*ny -= p->plane_y * MOVE_SPEED;
	}
}

void	move_player(t_game *game, int keycode)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &game->player;
	new_x = p->pos_x;
	new_y = p->pos_y;
	calc_new_pos(p, keycode, &new_x, &new_y);
	if (game->map.grid[(int)p->pos_y][(int)new_x] != '1')
		p->pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)p->pos_x] != '1')
		p->pos_y = new_y;
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
**
** TODO (Mario):
**   Pick angle: KEY_LEFT -> -ROT_SPEED, KEY_RIGHT -> ROT_SPEED
**   Apply rotation matrix to game->player.dir_x/dir_y
**   Apply same rotation to game->player.plane_x/plane_y
*/
void	rotate_player(t_game *game, int keycode)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;
	double		rot_speed;

	p = &game->player;
	if (keycode == KEY_LEFT)
		rot_speed = -ROT_SPEED;
	else
		rot_speed = ROT_SPEED;
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
}
