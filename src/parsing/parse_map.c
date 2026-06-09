/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/09 13:39:41 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** parse_map
**
** Subject rules for the map section:
**   - Map is ALWAYS the last section of the .cub file.
**   - Valid characters: '0' (empty), '1' (wall), ' ' (void/outside),
**     'N', 'S', 'E', 'W' (player start – exactly one required).
**   - Spaces are valid inside the map and must be preserved as-is.
**   - The map must be closed/surrounded by walls.
**   - Player start position sets pos_x/pos_y and start_dir on t_player.
**
** Returns 0 on success, 1 on any misconfiguration.
*/
 

static void	set_player_pos(t_player *player)
{
    if (player->start_dir == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    else if (player->start_dir == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;
        player->plane_x = -0.66;
        player->plane_y = 0;
    }
    else if (player->start_dir == 'E')
    {
        player->dir_x = 1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
    else if (player->start_dir == 'W')
    {
        player->dir_x = -1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
}

static int check_options(char option)
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

int parse_map(t_player *player, char **lines)
{
    int i;
    int j;
    int pos_confirm;

    pos_confirm = 0;
    i = 0;
    while (lines[i])
    {
        j = 0;
        while (lines[i][j])
        {
            if (lines[i][j] == ' ')
                j++;
            else if (lines[i][j] == '1' || lines[i][j] == '0')
                j++;
            else if (check_options(lines[i][j]) == 0)
            {
                if (pos_confirm == 1)
                    return (1);
                pos_confirm = 1;
                player->start_dir = lines[i][j];
                player->pos_x = (double)j + 0.5;
                player->pos_y = (double)i + 0.5;
                lines[i][j] = '0';
                j++;
            }
            else
                return (1);
        }
        i++;
    }
    if (pos_confirm == 0)
        return (1);
    set_player_pos(player);
    return (0);
}
