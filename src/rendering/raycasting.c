/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** cast_rays
**
** Core raycasting loop – one ray per screen column (x = 0 .. WIN_W-1).
**
** DDA algorithm steps (see Lode's tutorial referenced in README):
**   1. camera_x   = 2 * x / WIN_W - 1           ([-1, 1] range)
**   2. ray_dir    = dir + plane * camera_x
**   3. delta_dist = |1 / ray_dir|                (avoid div-by-zero)
**   4. step & side_dist initialisation
**   5. DDA loop: advance to next grid cell until a wall ('1') is hit
**   6. perp_wall_dist  (corrects fisheye distortion)
**   7. line_height, draw_start, draw_end
**   8. tex_x (which column inside the texture to sample)
**   9. Call draw_wall_slice for the column
*/
void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		col;

	col = 0;
	while (col < WIN_W)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		/* TODO (Mario): fill ray fields and run DDA here */
		(void)ray;
		col++;
	}
	(void)game;
}
