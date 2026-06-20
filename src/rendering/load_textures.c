/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/20 12:40:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

mlx_texture_t	*alloc_texture(int w, int h)
{
	mlx_texture_t	*tex;

	tex = malloc(sizeof(mlx_texture_t));
	if (!tex)
		return (NULL);
	tex->width = w;
	tex->height = h;
	tex->bytes_per_pixel = 4;
	tex->pixels = ft_calloc(w * h * 4, 1);
	if (!tex->pixels)
	{
		free(tex);
		return (NULL);
	}
	return (tex);
}

uint32_t	find_color(t_xpm_color *colors, int color_count,
		const char *key, int cpp)
{
	int	i;

	i = 0;
	while (i < color_count)
	{
		if (ft_strncmp(colors[i].key, key, cpp) == 0)
			return (colors[i].color);
		i++;
	}
	return (0xFF00FFFF);
}

int	load_textures(t_game *game)
{
	game->tex.no.texture = load_xpm(game->tex.no_path);
	if (!game->tex.no.texture)
		return (print_error(ERR_TEX_LOAD), 1);
	game->tex.no.width = (int)game->tex.no.texture->width;
	game->tex.no.height = (int)game->tex.no.texture->height;
	game->tex.so.texture = load_xpm(game->tex.so_path);
	if (!game->tex.so.texture)
		return (print_error(ERR_TEX_LOAD), 1);
	game->tex.so.width = (int)game->tex.so.texture->width;
	game->tex.so.height = (int)game->tex.so.texture->height;
	game->tex.we.texture = load_xpm(game->tex.we_path);
	if (!game->tex.we.texture)
		return (print_error(ERR_TEX_LOAD), 1);
	game->tex.we.width = (int)game->tex.we.texture->width;
	game->tex.we.height = (int)game->tex.we.texture->height;
	game->tex.ea.texture = load_xpm(game->tex.ea_path);
	if (!game->tex.ea.texture)
		return (print_error(ERR_TEX_LOAD), 1);
	game->tex.ea.width = (int)game->tex.ea.texture->width;
	game->tex.ea.height = (int)game->tex.ea.texture->height;
	return (0);
}
