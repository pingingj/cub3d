/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:07:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/26 19:55:12 by dgarcez-         ###   ########.fr       */
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
		print_errors(game, 0, "Empty File", fd);
		return (false);
	}
	game->map.breakp++;
	while (line != NULL)
	{
		if (check_line(line, game) == false)
			return (free(line), false);
		free(line);
		if (game->ass.floor.nums && game->ass.ceiling.nums
			&& game->ass.walls[NO].filename && game->ass.walls[EA].filename
			&& game->ass.walls[WE].filename && game->ass.walls[SO].filename)
			break ;
		line = get_next_line(fd);
		game->map.breakp++;
	}
	return (true);
}

bool	parse(t_game *game, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	game->player.posx = -1;
	game->player.posy = -1;
	if (fd == -1)
		print_errors(game, 0, "Invalid file or no file provided", fd);
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
		print_errors(game, 0, "File is not in the correct format", fd);
	if (get_textures(game, fd) == false)
		print_errors(game, 1, "Invalid texture", fd);
	if (!game->ass.ceiling.nums || !game->ass.floor.nums
		|| !game->ass.walls[NO].filename || !game->ass.walls[EA].filename
		|| !game->ass.walls[WE].filename || !game->ass.walls[SO].filename)
		print_errors(game, 1, "Missing texture or color", fd);
	parse_colors(game, fd);
	parse_map(game, fd, filename);
	close(fd);
	return (true);
}
