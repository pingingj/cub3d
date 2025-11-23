/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:07:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/11/20 16:50:20 by dgarcez-         ###   ########.fr       */
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

void	check_walls(char *line, t_game *game)
{
	char	*letters[7];
	int		i;

	i = -1;
	letters[NO] = "NO ";
	letters[EA] = "EA ";
	letters[WE] = "WE ";
	letters[SO] = "SO ";
	letters[CL] = "CL ";
	letters[EN] = "EN ";
	letters[DO] = "DO ";
	while (++i < 7)
	{
		if (ft_strncmp(line, letters[i], 3) == 0
			&& !game->ass.textures[i].filename)
		{
			if (check_texture(line, &game->ass.textures[i].filename,
					'W') == false)
			{
				free(line);
				print_errors(game, 1 , "Invalid texture input");
			}
			return ;
		}
	}
	free(line);
	print_errors(game, 1, "Invalid input only 'NO', 'EA', 'WE', 'SO', 'C', 'F', 'EN', 'DO' and 'CL' available");
}

bool	check_line(char *line, t_game *game)
{
	skip_wspaces(&line);
	if (line[0] == '\0' || line[0] == '\n')
		return (true);
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (check_texture(line, &game->ass.ceiling.nums, 'C') == false)
		{
			free(line);
			print_errors(game, 1, "Invalid ceiling input");
		}
		return (true);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (check_texture(line, &game->ass.floor.nums, 'F') == false)
		{
			free(line);
			print_errors(game, 1, "Invalid floor input");
		}
		return (true);
	}
	check_walls(line, game);
	return (true);
}

bool	is_map(char *line)
{
	int	i;

	i = 0;
	while(line[i] && ft_strchr(" \t\v\f\r", line[i]))
		i++;
	if (line[i] == '\n')
		return (false);
	while(line[i])
	{
		if (ft_strchr(" C10JDNEWS\n", line[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

char	*get_textures(t_game *game)
{
	char	*line;

	line = get_next_line(game->fd);
	if (line == NULL)
		print_errors(game, 0, "Empty File");
	while (line != NULL)
	{
		if (is_map(line) == true)
			return (line);
		game->map.breakp++;
		check_line(line, game);
		free(line);
		line = get_next_line(game->fd);
	}
	return (NULL);
}

void	get_error(t_game *game, char *line)
{
	(void)line;
	if (game->ass.textures[NO].filename == NULL)
		print_errors(game, 1, "Missing north texture");
	else if (game->ass.textures[EA].filename == NULL)
		print_errors(game, 1, "Missing east texture");
	else if (game->ass.textures[WE].filename == NULL)
		print_errors(game, 1, "Missing west texture");
	else if (game->ass.textures[SO].filename == NULL)
		print_errors(game, 1, "Missing south texture");
	else
		print_errors(game, 1, "Error validating textures");
}

void	coin_pos(t_game *game)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	index = 0;
	game->ass.sprites = ft_calloc(game->ass.collect_amount + 1,
			sizeof(t_sprite));
	if (game->ass.sprites == NULL)
		print_errors(game, 1, "Failed malloc in spritess");
	while (y < game->map.pos.y)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'c')
			{
				game->ass.sprites[index].enemy = false;
				game->ass.sprites[index].exists = true;
				game->ass.sprites[index].cords.x = x + 0.5;
				game->ass.sprites[index].cords.y = y + 0.5;
				index++;
			}
			x++;
		}
		y++;
	}
}

void	make_sprites(t_game *game)
{
	int	x;
	int	y;
	int	amount;

	amount = 0;
	y = 0;
	while (y < game->map.pos.y)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'C')
				print_errors(game, 1, "Unreachable collectible found");
			if (game->map.grid[y][x] == 'c')
				amount++;
			x++;
		}
		y++;
	}
	game->ass.collect_amount = amount + 1;
	if(amount > 0)
		game->g_flags.collectibles_exist = true;
	if(amount > 0 && !game->ass.textures[CL].filename)
		print_errors(game,1,"Missing collectible texutre");
	coin_pos(game);
	if(game->ass.enemy.cords.x != -1)
	{
		game->ass.sprites[amount].exists = true;
		game->ass.sprites[amount].enemy = true;
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
	if (amount > 1)
		print_errors(game, 1, "Overworked");
	if (amount == 0)
	{
		game->ass.enemy.cords.x = -1;
		return ;
	}
	if (amount == 1 && !game->ass.textures[EN].filename)
		print_errors(game, 1, "Missing texture for the enemy");
	game->visited = ft_calloc(game->map.pos.y + 1, sizeof(int *));
	if (game->visited == NULL)
		print_errors(game, 1, "Malloc fail in make_enemy");
	game->prev = ft_calloc(game->map.pos.y + 1, sizeof(t_point *));
	if (game->prev == NULL)
	{
		free(game->visited);
		print_errors(game, 1, "Malloc fail in make_enemy");
	}
	y = 0;
	while (y < game->map.pos.y)
	{
		game->visited[y] = ft_calloc(game->map.pos.x, sizeof(int));
		game->prev[y] = ft_calloc(game->map.pos.x, sizeof(t_point));
		y++;
	}
}

void	init_vars(t_game *game)
{
	game->mini.tile_size = 60;
	game->mini.show = true;
	game->g_flags.laggy_lantern = true;
	game->player.posx = -1;
	game->player.posy = -1;
	game->player.look = 0;
}

bool	parse(t_game *game, char *filename)
{
	char	*line;
	init_vars(game);
	game->fd = open(filename, O_RDONLY);
	if (game->fd == -1)
		print_errors(game, 0, "Invalid file or no file provided");
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
		print_errors(game, 0, "File is not in the correct format");
	line = get_textures(game);
	if (!game->ass.ceiling.nums || !game->ass.floor.nums
		|| !game->ass.textures[NO].filename || !game->ass.textures[EA].filename
		|| !game->ass.textures[WE].filename || !game->ass.textures[SO].filename)
		print_errors(game, 1, "Missing texture or color");
	parse_colors(game);
	parse_map(game, filename, line);
	close(game->fd);
	make_enemy(game);
	make_sprites(game);
	return (true);
}
