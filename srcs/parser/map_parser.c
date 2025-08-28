/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/28 14:34:18 by dgarcez-         ###   ########.fr       */
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
				game->player.dirx = 0;
				game->player.diry = 0;
				game->player.planex = 0;
				game->player.planey = 0;
				if (game->map.grid[y][x] == 'N')
				{
					game->player.diry = -1;
					game->player.planex = 0.66;
				}
				if (game->map.grid[y][x] == 'S')
				{
					game->player.diry = 1;
					game->player.planex = -0.66;
				}
				if (game->map.grid[y][x] == 'E')
				{
					game->player.dirx = 1;
					game->player.planey = 0.66;
				}
				if (game->map.grid[y][x] == 'W')
				{
					game->player.dirx = -1;
					game->player.planey = -0.66;
				}
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
		return (false);
	return (true);
}

char	*around_walls(t_map map, t_game game, int x, int y)
{
	if (map.grid[y][x] == 'd')
	{
		if (y - 1 < 0 || y + 1 > game.map.pos.y || x - 1 < 0 || x + 1 > ft_strlen(map.grid[y]))
			return ("Out of bounds door");
		if (map.grid[y - 1][x] == 'd' || map.grid[y + 1][x] == 'd' || map.grid[y][x -1] == 'd' || map.grid[y][x + 1] == 'd')
			return ("This ain't fancy no double doors");
		if (map.grid[y - 1][x] == '1' && map.grid[y + 1][x] == '1' && (map.grid[y][x - 1] != '1' && map.grid[y][x + 1] != '1'))
			return(NULL);
		else if (map.grid[y][x - 1] == '1' && map.grid[y][x + 1] == '1' && (map.grid[y - 1][x] != '1' && map.grid[y + 1][x] != '1'))
			return (NULL);
		else
			return ("Doors are not between 2 walls");
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

void	parse_map(t_game *game, int fd, char *filename)
{
	char	*funny_msg;
	get_map(game, fd, filename);
	if (check_map(game) == false)
		print_errors(game, 1, "Invalid char found", fd);
	if (get_player(game) == false)
		print_errors(game, 1, "Player not found or multiple players in map",
			fd);
	if (flood_fill(&game->map) == false)
		print_errors(game, 1, "Map is invalid", fd);
	funny_msg = check_doors(game->map, *game);
	if (funny_msg != NULL)
		print_errors(game, 1, funny_msg, fd);
}
