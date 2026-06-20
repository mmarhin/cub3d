/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/20 12:00:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	read_header(int fd, t_xpm_hdr *hdr)
{
	char	*line;
	char	*q;

	line = ft_get_next_line(fd);
	while (line)
	{
		q = get_quoted_string(line);
		if (q && parse_xpm_header(q, hdr) == 0)
		{
			free(q);
			free(line);
			return (0);
		}
		free(q);
		free(line);
		line = ft_get_next_line(fd);
	}
	return (1);
}

void	skip_rest(int fd)
{
	char	*line;

	line = ft_get_next_line(fd);
	while (line)
	{
		free(line);
		line = ft_get_next_line(fd);
	}
}

void	cleanup_state(t_xpm_state *state)
{
	int	i;

	i = 0;
	if (state->colors)
	{
		while (i < state->hdr.color_count)
			free(state->colors[i++].key);
		free(state->colors);
	}
}

void	clean_tex(t_xpm_state *state)
{
	if (state->tex)
		mlx_delete_texture(state->tex);
	state->tex = NULL;
}
