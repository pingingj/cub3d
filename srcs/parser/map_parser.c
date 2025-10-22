/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/21 14:05:29 by dgarcez-         ###   ########.fr       */
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
			if (ft_strchr("01 NEWSDCJ\n", game->map.grid[y][x]) == NULL)
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
		print_errors(game, 1, "Missing player in map");
	return (true);
}

char	*around_walls(t_map map, t_game game, int x, int y)
{
	if (map.grid[y][x] == 'd')
	{
		if (map.grid[y][x] == 'd' && !game.ass.textures[DO].filename)
			return ("Missing texture for doors");
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

bool	change_map(t_map *map)
{
	char 	**new;
	int		i;
	int		j;

	i = 0;
	new = ft_calloc(map->pos.y + 1, sizeof(char *));
	if (new == NULL)
		return (false);
	while (i < map->pos.y)
	{
		j = 0;
		new[i] = ft_calloc(map->pos.x + 1, sizeof(char));
		if (new[i] == NULL)
			return (freetrix(new), false);
		new[i] = ft_memcpy(new[i], map->grid[i], ft_strlen(map->grid[i]));
		while(new[i][j] != '\n' && new[i][j])
			j++;
		while(j < map->pos.x)
		{
			new[i][j] = ' ';
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
	freetrix(map->grid);
	map->grid = new;
	return (true);
}

void	parse_map(t_game *game, char *filename, char *line)
{
	char	*funny_msg;

	get_map(game, filename, line);
	if (check_map(game) == false)
		print_errors(game, 1, "Invalid char found");
	if (get_player(game) == false)
		print_errors(game, 1, "Player not found or multiple players in map");
	if (flood_fill(&game->map) == false)
		print_errors(game, 1, "Map is invalid");
	funny_msg = check_doors(game->map, *game);
	if (funny_msg != NULL)
		print_errors(game, 1, funny_msg);
	if (change_map(&game->map) == false)
		print_errors(game, 1, "Error while changing map grid");
}
