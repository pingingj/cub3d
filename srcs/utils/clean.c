/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:12:18 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/25 18:22:42 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	print_map(t_map map)
{
	int	i;

	i = 0;
	while (i < map.pos.y)
	{
		ft_printf("%s", map.grid[i]);
		i++;
	}
	// ft_printf("PLAYER positions X = %d, Y = %d\n", map.player.pos.x,
	// 	map.player.pos.y);
	// ft_printf("COLLETIBLE AMOUNT = %d\n", map.c_amount);
	// ft_printf("EXIT position: X = %d, Y = %d\n",
	// 	map.exit.pos.x, map.exit.pos.y);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->ass.ceiling.nums)
		free(game->ass.ceiling.nums);
	if (game->ass.floor.nums)
		free(game->ass.floor.nums);
	if (game->map.grid)
		freetrix(game->map.grid);
	while(i < 4)
	{
		if (game->ass.walls[i].filename)
			free(game->ass.walls[i].filename);
		i++;
	}
}

void	print_errors(t_game *game, int error, char *msg)
{
	ft_dprintf(2, "Error\n%s\n", msg);
	if (error == 1)
		free_game(game);
	exit(error);
}