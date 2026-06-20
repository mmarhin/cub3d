/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/20 12:00:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	read_one_color(int fd, t_xpm_color *color, int cpp)
{
	char	*line;
	char	*q;

	line = ft_get_next_line(fd);
	if (!line)
		return (1);
	q = get_quoted_string(line);
	if (q)
	{
		color->key = ft_substr(q, 0, cpp);
		color->color = get_color_value(q, cpp);
		free(q);
	}
	free(line);
	return (0);
}

static t_xpm_color	*read_colors(int fd, int color_count, int cpp)
{
	t_xpm_color	*colors;
	int			i;

	colors = ft_calloc(color_count, sizeof(t_xpm_color));
	if (!colors)
		return (NULL);
	i = 0;
	while (i < color_count)
	{
		if (read_one_color(fd, &colors[i], cpp))
			break ;
		i++;
	}
	if (i < color_count)
	{
		while (--i >= 0)
			free(colors[i].key);
		return (free(colors), NULL);
	}
	return (colors);
}

static void	fill_pixel_row(t_xpm_state *state, char *q, int y)
{
	int			x;
	uint32_t	color;
	int			idx;

	x = 0;
	while (x < state->hdr.w)
	{
		color = find_color(state->colors, state->hdr.color_count,
				q + x * state->hdr.cpp, state->hdr.cpp);
		idx = y * state->hdr.w + x;
		state->tex->pixels[idx * 4 + 0] = (color >> 24) & 0xFF;
		state->tex->pixels[idx * 4 + 1] = (color >> 16) & 0xFF;
		state->tex->pixels[idx * 4 + 2] = (color >> 8) & 0xFF;
		state->tex->pixels[idx * 4 + 3] = color & 0xFF;
		x++;
	}
}

static int	read_pixels(int fd, t_xpm_state *state)
{
	char	*line;
	char	*q;
	int		y;

	y = 0;
	while (y < state->hdr.h)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		q = get_quoted_string(line);
		if (q)
		{
			fill_pixel_row(state, q, y);
			free(q);
			y++;
		}
		free(line);
	}
	return (y == state->hdr.h);
}

mlx_texture_t	*load_xpm(const char *path)
{
	int				fd;
	t_xpm_state		state;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read_header(fd, &state.hdr))
		return (close(fd), NULL);
	state.colors = read_colors(fd, state.hdr.color_count, state.hdr.cpp);
	if (!state.colors)
		return (close(fd), NULL);
	state.tex = alloc_texture(state.hdr.w, state.hdr.h);
	if (!state.tex || !read_pixels(fd, &state))
		clean_tex(&state);
	cleanup_state(&state);
	skip_rest(fd);
	close(fd);
	return (state.tex);
}
