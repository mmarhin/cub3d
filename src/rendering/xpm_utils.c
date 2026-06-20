/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/20 12:00:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static uint32_t	parse_hex_color(const char *str)
{
	uint32_t	color;
	int			i;
	int			val;

	if (str[0] == '#')
		str++;
	color = 0;
	i = 0;
	while (i < 6)
	{
		if (str[i] >= '0' && str[i] <= '9')
			val = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			val = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			val = str[i] - 'A' + 10;
		else
			return (0xFF0000FF);
		color = (color << 4) | val;
		i++;
	}
	return ((color << 8) | 0xFF);
}

char	*get_quoted_string(char *line)
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

static int	read_int(const char *str, int *i)
{
	int	val;

	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	val = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		val = val * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (val);
}

int	parse_xpm_header(char *q, t_xpm_hdr *hdr)
{
	int	i;

	i = 0;
	hdr->w = read_int(q, &i);
	hdr->h = read_int(q, &i);
	hdr->color_count = read_int(q, &i);
	hdr->cpp = read_int(q, &i);
	if (hdr->w <= 0 || hdr->h <= 0 || hdr->color_count <= 0 || hdr->cpp <= 0)
		return (1);
	return (0);
}

uint32_t	get_color_value(char *q, int cpp)
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
