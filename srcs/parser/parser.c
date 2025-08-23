/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:07:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/23 22:06:26 by daniel           ###   ########.fr       */
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

bool	get_textures(char *filename, t_game *game, int fd)
{
	char	*line;

	(void)filename;
	line = get_next_line(fd);
	if (line == NULL)
	{
		print_errors(game, 3, "Empty File");
		return (false);
	}
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
	}
	return (true);
}

bool	parse(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_errors(game, 1, "Invalid file or no file provided");
		return (false);
	}
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
	{
		close(fd);
		print_errors(game, 1, "File is not in the correct format");
		return (false);
	}
	if (get_textures(filename, game, fd) == false)
	{
		close(fd);
		print_errors(game, 2, "Invalid texture");
	}
	if (!game->ass.ceiling.nums || !game->ass.floor.nums || !game->ass.walls[NO].filename 
		|| !game->ass.walls[EA].filename || !game->ass.walls[WE].filename || !game->ass.walls[SO].filename)
	{
		close(fd);
		print_errors(game, 2, "Missing texture or color");
	}
	if (get_colors(&game->ass.ceiling) == false || get_colors(&game->ass.floor) == false)
	{
		close(fd);
		print_errors(game, 2, "Colors aren't valid");
	}
	if (check_colors(game->ass.ceiling) == false || check_colors(game->ass.floor) == false)
	{
		close(fd);
		print_errors(game, 2, "Colors values aren't valid");
	}
	close(fd);
	return (true);
}
