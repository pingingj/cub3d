/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/26 19:59:11 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool	flood_fill(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (ft_strchr("0NEWSD", map->grid[y][x]) != NULL)
				if (flood_map(map, x, y) == false)
					return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (ft_strchr("01 NEWSD\n", game->map.grid[y][x]) == NULL)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	get_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (ft_strchr("NEWS", game->map.grid[y][x]))
			{
				if (game->player.posx > 0 && game->player.posy > 0)
					return (false);
				game->player.posx = x;
				game->player.posy = y;
			}
			x++;
		}
		y++;
	}
	if (game->player.posx == -1 || game->player.posy == -1)
		return (false);
	return (true);
}

void	parse_map(t_game *game, int fd, char *filename)
{
	get_map(game, fd, filename);
	if (check_map(game) == false)
		print_errors(game, 1, "Invalid char found", fd);
	if (get_player(game) == false)
		print_errors(game, 1, "Player not found or multiple players in map",
			fd);
	if (flood_fill(&game->map) == false)
		print_errors(game, 1, "Map is invalid", fd);
}
