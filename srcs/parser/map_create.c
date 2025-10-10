/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:50:51 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/06 16:56:59 by dgarcez-         ###   ########.fr       */
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
		|| ft_strchr("10oDdCcNEWSnews", map->grid[y][x]) == NULL)
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
	if (in_string(line, "10NEWSDC") == false && game->map.exists == false)
		game->map.breakp++;
	else
		game->map.exists = true;
	i++;
}

static bool	get_grid(t_game *game, char *filename)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_errors(game, 1, "Wasn't able to open file", -1);
	i = 0;
	while (i < game->map.breakp)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	i = 0;
	while (1)
	{
		game->map.grid[i] = get_next_line(fd);
		if (game->map.grid[i] == NULL)
			return (close(fd), true);
		i++;
	}
	close(fd);
	return (true);
}

bool	get_map(t_game *game, int fd, char *filename)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		print_errors(game, 1, "No map found", fd);
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
		line = get_next_line(fd);
	}
	game->map.grid = ft_calloc(game->map.pos.y + 1, sizeof(char *));
	if (game->map.grid == NULL)
		return (false);
	close(fd);
	get_grid(game, filename);
	return (true);
}
