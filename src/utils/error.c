/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/05/26 12:00:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** print_error
**
** Subject: if any misconfiguration is encountered, the program must
**          exit properly and return "Error\n" followed by an explicit
**          error message.
**
** Writes "Error\n" + msg to stderr, returns 1 for convenience
** (callers can do: return (print_error(ERR_XXX));).
*/
int	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return (1);
}

/*
** exit_error
**
** Prints the error, cleans up, and exits.
** Use only when MLX / full game state is already initialised.
*/
void	exit_error(t_game *game, char *msg)
{
	print_error(msg);
	if (game)
		cleanup_game(game);
	exit(1);
}
