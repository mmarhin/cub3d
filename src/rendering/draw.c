/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** draw_background
**
** Subject: program must be able to set floor and ceiling to two
**          different colors (from F and C identifiers).
**
** Fills the top half of the image with ceiling color,
** the bottom half with floor color.
*/
void	draw_background(t_game *game)
{
	/* TODO (Mario):
	**   Iterate y from 0 to WIN_H:
	**     If y < WIN_H / 2 → put ceiling color pixel
	**     Else             → put floor color pixel
	**   Use game->ceiling and game->floor (t_color structs from Manuel).
	**   Convert (r,g,b) → single int: (r << 16) | (g << 8) | b
	**   Write directly into game->mlx.img.addr.
	*/
	(void)game;
}

/*
** draw_wall_slice
**
** Draws one vertical column of pixels using the correct directional
** texture. Subject requires textures to differ by wall side (N/S/E/W).
**
** ray->side and ray->ray_dir determine which t_tex to use:
**   side == 1 && ray_dir_y < 0  → NO (North)
**   side == 1 && ray_dir_y > 0  → SO (South)
**   side == 0 && ray_dir_x > 0  → EA (East)
**   side == 0 && ray_dir_x < 0  → WE (West)
*/
void	draw_wall_slice(t_game *game, int col, t_ray *ray)
{
	/* TODO (Mario):
	**   1. Select the correct t_tex* based on ray->side + ray_dir.
	**   2. For each y in [ray->draw_start, ray->draw_end]:
	**      a. Compute tex_y from the texture height and y.
	**      b. Get pixel color with get_tex_color(tex, ray->tex_x, tex_y).
	**      c. Write to img.addr at (col, y).
	*/
	(void)game;
	(void)col;
	(void)ray;
}

/*
** render_frame
**
** Draws one full frame: background → cast all rays → push image.
** Subject: strongly recommends using mlx images for performance.
*/
void	render_frame(t_game *game)
{
	draw_background(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.img.img, 0, 0);
}
