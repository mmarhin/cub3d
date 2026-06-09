/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/06/09 15:05:36 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** check_args
**
** Subject: program must take exactly one argument, a scene file
**          with the .cub extension.
**
** Returns 0 on success, 1 (after printing Error\n + message) on failure.
*/
int	check_args(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
		return (print_error(ERR_ARGS));
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		return (print_error(ERR_EXT));
	return (0);
}
