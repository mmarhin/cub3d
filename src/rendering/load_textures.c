/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/20 12:35:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_hex(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

static int	hex_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

static uint32_t	parse_hex_color(const char *str)
{
	uint32_t	r, g, b;

	if (str[0] == '#')
		str++;
	if (!is_hex(str[0]) || !is_hex(str[1]) || !is_hex(str[2])
		|| !is_hex(str[3]) || !is_hex(str[4]) || !is_hex(str[5]))
		return (0xFF0000FF);
	r = (hex_val(str[0]) << 4) | hex_val(str[1]);
	g = (hex_val(str[2]) << 4) | hex_val(str[3]);
	b = (hex_val(str[4]) << 4) | hex_val(str[5]);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

typedef struct s_xpm_color {
	char		*key;
	uint32_t	color;
} t_xpm_color;

static char	*get_quoted_string(char *line)
{
	char	*start;
	char	*end;

	start = ft_strchr(line, '"');
	if (!start)
		return (NULL);
	start++;
	end = ft_strchr(start, '"');
	if (!end)
		return (NULL);
	return (ft_substr(start, 0, end - start));
}

static int	skip_spaces(const char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

static int	read_int(const char *str, int *i)
{
	int	val;

	*i = skip_spaces(str, *i);
	val = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		val = val * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (val);
}

static int	parse_xpm_header(char *q, int *w, int *h, int *colors, int *cpp)
{
	int	i;

	i = 0;
	*w = read_int(q, &i);
	*h = read_int(q, &i);
	*colors = read_int(q, &i);
	*cpp = read_int(q, &i);
	if (*w <= 0 || *h <= 0 || *colors <= 0 || *cpp <= 0)
		return (1);
	return (0);
}

static mlx_texture_t	*alloc_texture(int w, int h)
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

static char	*get_color_key(char *q, int cpp)
{
	return (ft_substr(q, 0, cpp));
}

static uint32_t	get_color_value(char *q, int cpp)
{
	char	*p;

	p = q + cpp;
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == 'c')
	{
		p++;
		while (*p == ' ' || *p == '\t')
			p++;
	}
	if (ft_strncmp(p, "None", 4) == 0 || ft_strncmp(p, "none", 4) == 0)
		return (0x00000000);
	if (*p == '#')
		return (parse_hex_color(p));
	return (0x000000FF);
}

static uint32_t	find_color(t_xpm_color *colors, int color_count, const char *key, int cpp)
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

static mlx_texture_t	*load_xpm(const char *path)
{
	int				fd;
	char			*line;
	char			*q;
	int				w, h, color_count, cpp;
	t_xpm_color		*colors;
	mlx_texture_t	*tex;
	int				i;
	int				y;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while ((line = ft_get_next_line(fd)))
	{
		q = get_quoted_string(line);
		if (q)
		{
			if (parse_xpm_header(q, &w, &h, &color_count, &cpp) == 0)
			{
				free(q);
				free(line);
				break ;
			}
			free(q);
		}
		free(line);
	}
	if (!line)
	{
		close(fd);
		return (NULL);
	}
	colors = ft_calloc(color_count, sizeof(t_xpm_color));
	if (!colors)
	{
		close(fd);
		return (NULL);
	}
	i = 0;
	while (i < color_count)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		q = get_quoted_string(line);
		if (q)
		{
			colors[i].key = get_color_key(q, cpp);
			colors[i].color = get_color_value(q, cpp);
			free(q);
			i++;
		}
		free(line);
	}
	if (i < color_count)
	{
		while (--i >= 0)
			free(colors[i].key);
		free(colors);
		close(fd);
		return (NULL);
	}
	tex = alloc_texture(w, h);
	if (!tex)
	{
		for (i = 0; i < color_count; i++)
			free(colors[i].key);
		free(colors);
		close(fd);
		return (NULL);
	}
	y = 0;
	while (y < h)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		q = get_quoted_string(line);
		if (q)
		{
			for (int x = 0; x < w; x++)
			{
				uint32_t color = find_color(colors, color_count, q + x * cpp, cpp);
				int idx = y * w + x;
				tex->pixels[idx * 4 + 0] = (color >> 24) & 0xFF;
				tex->pixels[idx * 4 + 1] = (color >> 16) & 0xFF;
				tex->pixels[idx * 4 + 2] = (color >> 8) & 0xFF;
				tex->pixels[idx * 4 + 3] = color & 0xFF;
			}
			free(q);
			y++;
		}
		free(line);
	}
	for (i = 0; i < color_count; i++)
		free(colors[i].key);
	free(colors);
	while ((line = ft_get_next_line(fd)))
		free(line);
	close(fd);
	if (y < h)
	{
		mlx_delete_texture(tex);
		return (NULL);
	}
	return (tex);
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
