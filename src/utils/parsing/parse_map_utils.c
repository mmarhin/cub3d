/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:26:28 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/18 13:29:58 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void player_dir_n(t_player *player)
{
    player->dir_x = 0;
    player->dir_y = -1;
    player->plane_x = 0.66;
    player->plane_y = 0;
}

void player_dir_s(t_player *player)
{
    player->dir_x = 0;
    player->dir_y = 1;
    player->plane_x = -0.66;
    player->plane_y = 0;
}

void player_dir_e(t_player *player)
{
    player->dir_x = 1;
    player->dir_y = 0;
    player->plane_x = 0;
    player->plane_y = 0.66;
}

void player_dir_w(t_player *player)
{
    player->dir_x = -1;
    player->dir_y = 0;
    player->plane_x = 0;
    player->plane_y = -0.66;
}