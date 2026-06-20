/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/20 12:23:26 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_player_pos(t_player *player)
{
    if (player->start_dir == 'N')
        player_dir_n(player);
	else if (player->start_dir == 'S')
        player_dir_s(player);
	else if (player->start_dir == 'E')
        player_dir_e(player);	
	else if (player->start_dir == 'W')
        player_dir_w(player);
}

static int	check_options(char option)
{
	if (option == 'N')
		return (0);
	else if (option == 'S')
		return (0);
	else if (option == 'E')
		return (0);
	else if (option == 'W')
		return (0);
	return (1);
}

static void player_start_pos(t_player *player, t_map *map, int i, int j)
{
    player->start_dir = map->grid[i][j];
    player->pos_x = (double)j + 0.5;
    player->pos_y = (double)i + 0.5;
    map->grid[i][j] = '0';
}

static int parse_row(t_map *map, t_player *player, int i, int *player_found)
{
    int j;

    j = 0;
    while (map->grid[i][j])
    {
        if (map->grid[i][j] == ' ' || map->grid[i][j] == '1' 
            || map->grid[i][j] == '0')
            j++;
        else if (check_options(map->grid[i][j]) == 0)
        {
            if (*player_found == 1)
                return (print_error(ERR_PLAYER), 1);
            *player_found = 1;
            player_start_pos(player, map, i, j);
            j++;
        }
        else
            return (print_error(ERR_MAP_CHAR), 1);
    }
    return (0);
}

int	parse_map(t_map *map, t_player *player)
{
    int		i;
    int		player_found;

    if (!map || !player || !map->grid)
        return (1);
    player_found = 0;
    i = 0;
    while (i < map->rows)
    {
        if (parse_row(map, player, i, &player_found))
            return (1);
        i++;
    }
    if (player_found == 0)
        return (print_error(ERR_PLAYER), 1);
    set_player_pos(player);
    return (0);
}
