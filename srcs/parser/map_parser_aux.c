/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:48:42 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/11/26 17:52:18 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	init_player(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.diry = -1;
		game->player.planex = 0.66;
	}
	else if (dir == 'S')
	{
		game->player.diry = 1;
		game->player.planex = -0.66;
	}
	else if (dir == 'E')
	{
		game->player.dirx = 1;
		game->player.planey = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dirx = -1;
		game->player.planey = -0.66;
	}
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
				init_player(game, game->map.grid[y][x]);
				if (game->player.posx > 0 && game->player.posy > 0)
					return (false);
				game->player.posx = x + 0.5;
				game->player.posy = y + 0.5;
			}
			x++;
		}
		y++;
	}
	if (game->player.posx == -1 || game->player.posy == -1)
		print_errors(game, 1, "Missing player in map");
	return (true);
}

char	*around_walls(t_map map, t_game game, int x, int y)
{
	if (map.grid[y][x] == 'd')
	{
		if (map.grid[y][x] == 'd' && !game.ass.textures[DO].filename)
			return ("Missing texture for doors");
		if (y - 1 < 0 || y + 1 > game.map.pos.y || x - 1 < 0
			|| x + 1 > ft_strlen(map.grid[y]))
			return ("Out of bounds door");
		if (map.grid[y - 1][x] == 'd' || map.grid[y + 1][x] == 'd'
			|| map.grid[y][x -1] == 'd' || map.grid[y][x + 1] == 'd')
			return ("This ain't fancy no double doors");
		if (map.grid[y - 1][x] == '1' && map.grid[y + 1][x] == '1'
			&& (map.grid[y][x - 1] != '1' && map.grid[y][x + 1] != '1'))
			return (NULL);
		else if (map.grid[y][x - 1] == '1' && map.grid[y][x + 1] == '1'
			&& (map.grid[y - 1][x] != '1' && map.grid[y + 1][x] != '1'))
			return (NULL);
		else
			return ("Doors must be surrounded by only 2 walls \
				(horizontally or vertically)");
	}
	return (NULL);
}

char	*check_doors(t_map map, t_game game)
{
	int		x;
	int		y;
	char	*msg;

	msg = NULL;
	y = 0;
	while (map.grid[y])
	{
		x = 0;
		while (map.grid[y][x])
		{
			msg = around_walls(map, game, x, y);
			if (msg != NULL)
				return (msg);
			x++;
		}
		y++;
	}
	return (msg);
}
