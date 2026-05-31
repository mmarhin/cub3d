/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mamarin-         ###   ########.fr       */
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
		|| parse_map(&game.map, &game.player, lines))
		return (free_lines(lines), cleanup_game(&game), 1);
	free_lines(lines);
	if (validate_map(&game.map))
		return (cleanup_game(&game), 1);
	if (init_mlx(&game))
		return (cleanup_game(&game), 1);
	if (load_textures(&game))
		return (cleanup_game(&game), 1);
	render_frame(&game);
	/* Subject: left/right arrows + WASD + ESC + window-close */
	mlx_hook(game.mlx.win, 2, 1L << 0, handle_keydown, &game);
	mlx_hook(game.mlx.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
