/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:07:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/15 14:55:12 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool check_texture(char *line, char **img, char c)
{
	int i;

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
	while (line[i] != '\0' && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] && line[i] != '\n')
		return (false);
	if (*img)
		return (false);
	(*img) = get_word(line, ' ');
	return (true);
}

bool check_walls(char *line, t_game *game)
{
	char *letters[4];
	int i;

	i = 0;
	letters[NO] = "NO ";
	letters[EA] = "EA ";
	letters[WE] = "WE ";
	letters[SO] = "SO ";
	while (i < 4)
	{
		if (ft_strncmp(line, letters[i], 3) == 0 && !game->ass.walls[i].filename)
		{
			if (check_texture(line, &game->ass.walls[i].filename, 'W') == false)
				return (false);
			return (true);
		}
		i++;
	}
	return (false);
}

bool check_line(char *line, t_game *game)
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

bool get_textures(t_game *game, int fd)
{
	char *line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		print_errors(game, 0, "Empty File", fd);
		return (false);
	}
	game->map.breakp++;
	while (line != NULL)
	{
		if (check_line(line, game) == false)
		{
			free(line);
			return (false);
		}
		free(line);
		if (game->ass.floor.nums && game->ass.ceiling.nums && game->ass.walls[NO].filename && game->ass.walls[EA].filename && game->ass.walls[WE].filename && game->ass.walls[SO].filename)
			break;
		line = get_next_line(fd);
		game->map.breakp++;
	}
	return (true);
}

void get_error(t_game *game, int fd)
{
	if (game->ass.floor.nums == NULL)
		print_errors(game, 1, "Missing floor color", fd);
	else if (game->ass.ceiling.nums == NULL)
		print_errors(game, 1, "Missing ceiling color", fd);
	else if (game->ass.walls[NO].filename == NULL)
		print_errors(game, 1, "Missing north texture", fd);
	else if (game->ass.walls[EA].filename == NULL)
		print_errors(game, 1, "Missing east texture", fd);
	else if (game->ass.walls[WE].filename == NULL)
		print_errors(game, 1, "Missing west texture", fd);
	else if (game->ass.walls[SO].filename == NULL)
		print_errors(game, 1, "Missing south texture", fd);
	else
		print_errors(game, 1, "Error validating textures or colors", fd);
}

void	coin_pos(t_game *game)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	index = 0;
	game->ass.collectible = ft_calloc(game->ass.collect_amount + 1, sizeof(t_sprite));
	if (game->ass.collectible == NULL)
		print_errors(game, 1, "Failed malloc in collectibles", -1);
	while (y < game->map.pos.y)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'c')
			{
				game->ass.collectible[index].exists = true;
				game->ass.collectible[index].cords.x = x + 0.5;
				game->ass.collectible[index].cords.y = y + 0.5;
				index++;
			}
			x++;
		}
		y++;
	}
	game->ass.collectible[game->ass.collect_amount -1].cords.x = 30;
	game->ass.collectible[game->ass.collect_amount - 1].cords.y = 19;
}

void	make_collectible(t_game *game)
{
	int			x;
	int			y;
	int			amount;

	amount = 0;
	y = 0;
	while (y < game->map.pos.y)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'C')
				print_errors(game, 1, "Not reachable collectible found", -1);	
			if (game->map.grid[y][x] == 'c')
				amount++;
			x++;
		}
		y++;
	}
	game->ass.collect_amount = amount;
	coin_pos(game);
}

void	make_enemy(t_game *game)
{
	int y;
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
				print_errors(game, 1, "Not enough experience", -1);
			if (game->map.grid[y][x] == 'j')
			{
				game->ass.enemy.cords.x = x;
				game->ass.enemy.cords.y = y;
				amount++;
			}
			x++;
		}
		y++;
	}
	if (amount > 1)
		print_errors(game, 1, "Overworked", -1);
	if (amount == 0)
	{
		game->ass.enemy.cords.x = -1;
		return ;
	}
	game->visited = ft_calloc(game->map.pos.y, sizeof(int *));
	if (game->visited == NULL)
		print_errors(game, 1, "Malloc fail in make_enemy", -1);
	game->prev = ft_calloc(game->map.pos.y, sizeof(t_point *));
	if (game->prev == NULL)
	{
		free(game->visited);
		print_errors(game, 1, "Malloc fail in make_enemy", -1);
	}
	y = 0;
	while (y < game->map.pos.y)
	{
		game->visited[y] = ft_calloc(game->map.pos.x, sizeof(int));
		game->prev[y] = ft_calloc(game->map.pos.x,sizeof(t_point));
		y++;
	}
}

bool parse(t_game *game, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_errors(game, 0, "Invalid file or no file provided", fd);
	game->mini.tile_size = 60;
	game->mini.show = true;
	game->player.posx = -1;
	game->player.posy = -1;
	game->player.look = 0;
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
		print_errors(game, 0, "File is not in the correct format", fd);
	if (get_textures(game, fd) == false)
		get_error(game, fd);
	if (!game->ass.ceiling.nums || !game->ass.floor.nums || !game->ass.walls[NO].filename || !game->ass.walls[EA].filename || !game->ass.walls[WE].filename || !game->ass.walls[SO].filename)
		print_errors(game, 1, "Missing texture or color", fd);
	parse_colors(game, fd);
	parse_map(game, fd, filename);
	close(fd);
	make_enemy(game);
	make_collectible(game);
	return (true);
}
