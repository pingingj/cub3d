/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:06:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/05 14:52:48 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool	parse_enemy(t_game *game, int amount)
{
	if (amount > 1)
		print_errors(game, 1, "Overworked");
	if (amount == 0)
	{
		game->ass.enemy.cords.x = -1;
		return (false);
	}
	if (amount == 1 && !game->ass.textures[EN].filename)
		print_errors(game, 1, "Missing texture for the enemy");
	return (true);
}

void	allocating_enemy(t_game *game)
{
	int	y;

	y = 0;
	game->visited = ft_calloc(game->map.pos.y + 1, sizeof(int *));
	if (game->visited == NULL)
		print_errors(game, 1, "Malloc fail in make_enemy");
	game->prev = ft_calloc(game->map.pos.y + 1, sizeof(t_point *));
	if (game->prev == NULL)
		print_errors(game, 1, "Malloc fail in make_enemy");
	while (y < game->map.pos.y)
	{
		game->visited[y] = ft_calloc(game->map.pos.x, sizeof(int));
		if (game->visited[y] == NULL)
			print_errors(game, 1, "Malloc fail in make_enemy");
		game->prev[y] = ft_calloc(game->map.pos.x, sizeof(t_point));
		if (game->prev[y] == NULL)
			print_errors(game, 1, "Malloc fail in make_enemy");
		y++;
	}
}

void	make_enemy(t_game *game)
{
	int	y;
	int	x;
	int	amount;

	amount = 0;
	y = 0;
	while (y < game->map.pos.y)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'J')
				print_errors(game, 1, "Not enough experience");
			if (game->map.grid[y][x] == 'j')
			{
				game->ass.enemy.cords.x = x + 0.5;
				game->ass.enemy.cords.y = y + 0.5;
				amount++;
			}
			x++;
		}
		y++;
	}
	if (parse_enemy(game, amount) == true)
		allocating_enemy(game);
}
