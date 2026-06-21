/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/21 10:31:48 by mamarin-         ###   ########.fr       */
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
**
** TODO (Mario):
**   Iterate y from 0 to WIN_H:
**     If y < WIN_H / 2 -> put ceiling color pixel
**     Else             -> put floor color pixel
**   Use game->ceiling and game->floor (t_color structs from Manuel).
**   Convert (r,g,b) -> single int: (r << 16) | (g << 8) | b
**   Write directly into game->mlx.img.addr.
*/
void	draw_background(t_game *game)
{
	int			x;
	int			y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	x = 0;
	ceiling_color = (game->ceiling.r << 24) | (game->ceiling.g << 16)
		| (game->ceiling.b << 8) | 0xFF;
	floor_color = (game->floor.r << 24) | (game->floor.g << 16)
		| (game->floor.b << 8) | 0xFF;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			if (y < WIN_H / 2)
				mlx_put_pixel(game->mlx.img.img, x, y, ceiling_color);
			else
				mlx_put_pixel(game->mlx.img.img, x, y, floor_color);
			y++;
		}
		x++;
	}
}

static t_tex	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&game->tex.ea);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (&game->tex.we);
	if (ray->side == 1 && ray->ray_dir_y > 0)
		return (&game->tex.so);
	return (&game->tex.no);
}

static uint32_t	get_wall_pixel(t_tex *tex, t_ray *ray, double *tex_pos,
		double step)
{
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	color = get_tex_color(tex, ray->tex_x, (int)*tex_pos & (tex->height - 1));
	*tex_pos += step;
	if (ray->side == 1)
	{
		r = ((color >> 24) * 3) / 4;
		g = (((color >> 16) & 0xFF) * 3) / 4;
		b = (((color >> 8) & 0xFF) * 3) / 4;
		color = (r << 24) | (g << 16) | (b << 8) | (color & 0xFF);
	}
	return (color);
}

void	draw_wall_slice(t_game *game, int col, t_ray *ray)
{
	t_tex	*tex;
	double	step;
	double	tex_pos;
	int		y;

	tex = get_texture(game, ray);
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		mlx_put_pixel(game->mlx.img.img, col, y,
			get_wall_pixel(tex, ray, &tex_pos, step));
		y++;
	}
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
	if (game->mlx.img.img->count == 0)
		mlx_image_to_window(game->mlx.mlx, game->mlx.img.img, 0, 0);
}
