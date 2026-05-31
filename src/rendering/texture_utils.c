/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** get_tex_color
**
** Returns the ARGB color of pixel (x, y) from a loaded t_tex.
** Formula: addr + (y * line_len + x * (bpp / 8))
*/
int	get_tex_color(t_tex *tex, int x, int y)
{
	char	*pixel;

	/* TODO (Mario): compute pixel address and dereference as int */
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}

/*
** calc_tex_x
**
** Computes ray->tex_x: the X column to sample inside the wall texture.
** Depends on the hit side and ray direction.
*/
void	calc_tex_x(t_game *game, t_ray *ray)
{
	/* TODO (Mario):
	**   1. wall_x = (side==0) ? player_y + perp_wall_dist*ray_dir_y
	**                         : player_x + perp_wall_dist*ray_dir_x
	**   2. wall_x -= floor(wall_x)        (fractional part)
	**   3. tex_x = (int)(wall_x * tex->width)
	**   4. Flip tex_x depending on ray direction so texture is not mirrored.
	*/
	(void)game;
	(void)ray;
}
