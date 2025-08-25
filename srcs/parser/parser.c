/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:07:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/25 20:53:08 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool	check_texture(char *line, char **img, char c)
{
	int	i;

	i = 0;
	if (c == 'C' || c == 'F')
		line += 1;
	else
		line += 2;
	skip_wspaces(&line);
	while (line[i] != '\0' && (line[i] != ' ' && (line[i] < 9 || line[i] > 13)))
		i++;
	if (line[0] == '\0' || ((c != 'C' && c != 'F') && (ft_strstr(line + i - 4,
					".xpm") == NULL)))
		return (false);
	while (line[i] != '\0' && (line[i] == ' ' || (line[i] >= 9
				&& line[i] <= 13)))
		i++;
	if (line[i] && line[i] != '\n')
		return (false);
	if (*img)
		return (false);
	(*img) = get_word(line, ' ');
	return (true);
}

bool	check_walls(char *line, t_game *game)
{
	char	*letters[4];
	int		i;

	i = 0;
	letters[NO] = "NO ";
	letters[EA] = "EA ";
	letters[WE] = "WE ";
	letters[SO] = "SO ";
	while (i < 4)
	{
		if (ft_strncmp(line, letters[i], 3) == 0
			&& !game->ass.walls[i].filename)
		{
			if (check_texture(line, &game->ass.walls[i].filename, 'W') == false)
				return (false);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_line(char *line, t_game *game)
{
	skip_wspaces(&line);
	if (line[0] == '\0' || line[0] == '\n')
		return (true);
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (check_texture(line, &game->ass.ceiling.nums, 'C') == false)
			return (false);
		return (true);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (check_texture(line, &game->ass.floor.nums, 'F') == false)
			return (false);
		return (true);
	}
	if (check_walls(line, game) == true)
		return (true);
	return (false);
}

bool	get_textures(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		print_errors(game, 0, "Empty File");
		return (false);
	}
	game->map.breakp++;
	while (line != NULL)
	{
		if (check_line(line, game) == false)
			return (free(line), false);
		free(line);
		if (game->ass.floor.nums && game->ass.ceiling.nums
			&& game->ass.walls[NO].filename
			&& game->ass.walls[EA].filename && game->ass.walls[WE].filename
			&& game->ass.walls[SO].filename)
			break ;
		line = get_next_line(fd);
		game->map.breakp++;
	}
	return (true);
}

void	find_map(t_game	*game, char *line)
{
	int	i;

	i = 0;
	while(line[i] && line[i] != '\0')
	{
		if (in_string(line, "10NEWSD") == false && game->map.exists == false)
			game->map.breakp++;
		else
			game->map.exists = true;
		i++;
	}
}

bool	get_grid(t_game	*game, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < game->map.breakp)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	i = 0;
	while(1)
	{
		game->map.grid[i] = get_next_line(fd);
		if (game->map.grid[i] == NULL)
			return (true);
		i++;
	}
	return (true);
}

bool	get_map(t_game *game, int fd, char *filename)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		print_errors(game, 1, "No map found");
		return (false);
	}
	while (line != NULL)
	{
		find_map(game, line);
		if (game->map.exists)
		{
			if (ft_strlen(line) > game->map.pos.x)
				game->map.pos.x = ft_strlen(line);
			game->map.pos.y++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map.grid = ft_calloc(game->map.pos.y + 1, sizeof(char *));
	close(fd);
	fd = open(filename, O_RDONLY);
	get_grid(game, fd);
	printf("map pos x %d y %d\n", game->map.pos.x, game->map.pos.y);
	return (true);
}

static bool	flood_map(t_map *map, int x, int y)
{
	// printf("char = %c x = %d y = %d\n", map->grid[y][x], x, y); 
	if (y >= 0 && y < map->pos.y && x >= 0 && x < map->pos.x && (map->grid[y][x] == '1' || map->grid[y][x] == 'o' || map->grid[y][x] == 'e'
		|| map->grid[y][x] == 'c' || map->grid[y][x] == 'd'))
		return (true);
	if (y < 0 || y >= map->pos.y || x < 0 || x >= map->pos.x || map->grid[y][x] == '\0'
		|| ft_strchr("10DocedNEWSnews", map->grid[y][x]) == NULL)
		return (false);
	if (map->grid[y][x] == '0')
		map->grid[y][x] = 'o';
	else if (map->grid[y][x] == 'N')
		map->grid[y][x] = 'n';
	else if (map->grid[y][x] == 'E')
		map->grid[y][x] = 'e';
	else if (map->grid[y][x] == 'W')
		map->grid[y][x] = 'w';
	else if (map->grid[y][x] == 'S')
		map->grid[y][x] = 's';
	else if (map->grid[y][x] == 'D')
		map->grid[y][x] = 'd';
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

bool	flood_fill(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while(map->grid[y][x])
		{
			if (ft_strchr("0NEWS", map->grid[y][x]) != NULL)
				if (flood_map(map, x, y) == false)
					return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	parse(t_game *game, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_errors(game, 0, "Invalid file or no file provided");
		return (false);
	}
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
	{
		close(fd);
		print_errors(game, 0, "File is not in the correct format");
		return (false);
	}
	if (get_textures(game, fd) == false)
	{
		close(fd);
		print_errors(game, 1, "Invalid texture");
	}
	if (!game->ass.ceiling.nums || !game->ass.floor.nums || !game->ass.walls[NO].filename 
		|| !game->ass.walls[EA].filename || !game->ass.walls[WE].filename || !game->ass.walls[SO].filename)
	{
		close(fd);
		print_errors(game, 1, "Missing texture or color");
	}
	if (get_colors(&game->ass.ceiling) == false || get_colors(&game->ass.floor) == false)
	{
		close(fd);
		print_errors(game, 1, "Colors aren't valid");
	}
	if (check_colors(game->ass.ceiling) == false || check_colors(game->ass.floor) == false)
	{
		close(fd);
		print_errors(game, 1, "Colors values aren't valid");
	}
	game->ass.ceiling.hexa = color_hexa(game->ass.ceiling);
	game->ass.floor.hexa = color_hexa(game->ass.floor);
	get_map(game, fd, filename);
	if (flood_fill(&game->map) == false)
	{
		close(fd);
		print_errors(game, 1, "Map is invalid");
	}
	
	return (true);
}
