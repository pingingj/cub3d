/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:50:51 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/14 16:57:14 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	change_grid(t_map *map, int x, int y)
{
	if (map->grid[y][x] == '0')
		map->grid[y][x] = 'o';
	else if (map->grid[y][x] == 'N')
		map->grid[y][x] = 'o';
	else if (map->grid[y][x] == 'E')
		map->grid[y][x] = 'o';
	else if (map->grid[y][x] == 'W')
		map->grid[y][x] = 'o';
	else if (map->grid[y][x] == 'S')
		map->grid[y][x] = 'o';
	else if (map->grid[y][x] == 'D')
		map->grid[y][x] = 'd';
	else if (map->grid[y][x] == 'C')
		map->grid[y][x] = 'c';
	else if (map->grid[y][x] == 'J')
		map->grid[y][x] = 'j';
}

bool	flood_map(t_map *map, int x, int y)
{
	if (y >= 0 && y < map->pos.y && x >= 0 && x < ft_strlen(map->grid[y]) && map->grid[y][x]
		&& (map->grid[y][x] == '1' || map->grid[y][x] == 'o'
			|| map->grid[y][x] == 'e' || map->grid[y][x] == 'c'
			|| map->grid[y][x] == 'd'))
		return (true);
	if (y < 0 || y >= map->pos.y || x < 0
		|| x >= ft_strlen(map->grid[y]) || map->grid[y][x] == '\0'
		|| ft_strchr("10oDdCcNEWSnewsJj", map->grid[y][x]) == NULL)
		return (false);
	change_grid(map, x, y);
	if (flood_map(map, x - 1, y) == false)
		return (false);
	if (flood_map(map, x + 1, y) == false)
		return (false);
	if (flood_map(map, x, y - 1) == false)
		return (false);
	if (flood_map(map, x, y + 1) == false)
		return (false);
	return (true);
}

static void	find_map(t_game *game, char *line)
{
	int	i;

	i = 0;
	if (in_string(line, "10NEWSDCJ") == false && game->map.exists == false)
	{
		while(line[i])
		{

			if (ft_isprint(line[i]) && (line[i] != ' ' || (line[i] < 9 && line[i] > 13)))
			{
				free(line);
				print_errors(game, 1, "Invalid character before map");
			}
			i++;
		}
		game->map.breakp++;
	}
	else
		game->map.exists = true;
}

static bool	get_grid(t_game *game, char *filename)
{
	int		i;
	char	*line;

	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		print_errors(game, 1, "Wasn't able to open file");
	i = 0;
	while (i < game->map.breakp)
	{
		line = get_next_line(game->fd);
		free(line);
		i++;
	}
	i = 0;
	while (1)
	{
		game->map.grid[i] = get_next_line(game->fd);
		if (game->map.grid[i] == NULL)
			return (close(game->fd), true);
		i++;
	}
	close(game->fd);
	return (true);
}

bool	get_map(t_game *game, char *filename)
{
	char	*line;

	line = get_next_line(game->fd);
	if (line == NULL)
		print_errors(game, 1, "No map found");
	while (line != NULL)
	{
		find_map(game, line);
		if (game->map.exists)
		{
			if (ft_strlen(line) > game->map.pos.x && line[ft_strlen(line) - 1] == '\n')
				game->map.pos.x = ft_strlen(line) - 1;
			else if (ft_strlen(line) > game->map.pos.x)
				game->map.pos.x = ft_strlen(line);
			game->map.pos.y++;
		}
		free(line);
		line = get_next_line(game->fd);
	}
	game->map.grid = ft_calloc(game->map.pos.y + 1, sizeof(char *));
	if (game->map.grid == NULL)
		return (false);
	close(game->fd);
	get_grid(game, filename);
	return (true);
}
