/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/06/09 16:34:41 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** main – entry point
**
** Subject requirements covered here:
**   - Exactly one argument: a scene file with .cub extension.
**   - Parse NO/SO/WE/EA textures, F and C colors, and the map.
**   - Map must be closed, contain valid chars, exactly one player.
**   - MLX window: arrow keys rotate, WASD move, ESC and red-cross exit cleanly.
*/
int	main(int argc, char **argv)
{
	t_game	game;
	char	**lines;

	ft_memset(&game, 0, sizeof(t_game));
	if (check_args(argc, argv))
		return (1);
	lines = read_cub_file(argv[1]);
	if (!lines)
		return (1);
	if (parse_textures(&game.tex, lines)
		|| parse_colors(&game.floor, &game.ceiling, lines)
		|| build_map_grid(lines, &game.map)
		|| parse_map(&game.map, &game.player))
		return (free_lines(lines), cleanup_game(&game), 1);
	free_lines(lines);
	if (validate_map(&game.map, &game.player))
		return (cleanup_game(&game), 1);
	if (init_mlx(&game))
		return (cleanup_game(&game), 1);
	if (load_textures(&game))
		return (cleanup_game(&game), 1);
	render_frame(&game);
	mlx_key_hook(game.mlx.mlx, handle_keydown, &game);
	mlx_close_hook(game.mlx.mlx, handle_close, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
