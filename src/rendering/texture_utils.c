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
	int		index;
	uint8_t	*p;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	if (!tex->texture || !tex->texture->pixels)
		return (0);
	index = (y * tex->width + x) * 4;
	p = &tex->texture->pixels[index];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

/*
** calc_tex_x
**
** Computes ray->tex_x: the X column to sample inside the wall texture.
** Depends on the hit side and ray direction.
**
** TODO (Mario):
**   1. wall_x = (side==0) ? player_y + perp_wall_dist*ray_dir_y
**                         : player_x + perp_wall_dist*ray_dir_x
**   2. wall_x -= floor(wall_x)        (fractional part)
**   3. tex_x = (int)(wall_x * tex->width)
**   4. Flip tex_x depending on ray direction so texture is not mirrored.
*/
void	calc_tex_x(t_game *game, t_ray *ray)
{
	(void)game;
	(void)ray;
}
