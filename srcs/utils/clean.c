/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:12:18 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/21 19:06:36 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->ass.ceiling.nums)
		free(game->ass.ceiling.nums);
	if (game->ass.floor.nums)
		free(game->ass.floor.nums);
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
	if (error == 4)
		free_game(game);
	else if (error == 5)
		free_game(game);
	exit(error);
}