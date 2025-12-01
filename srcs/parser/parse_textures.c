/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:58:52 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/11/26 19:04:00 by dgarcez-         ###   ########.fr       */
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
	char	**letters;
	int		i;

	i = -1;
	letters = letters_init();
	while (++i < 7)
	{
		if (ft_strncmp(line, letters[i], 3) == 0
			&& !game->ass.textures[i].filename)
		{
			if (check_texture(line, &game->ass.textures[i].filename,
					'W') == false)
			{
				free(line);
				print_errors(game, 1, "Invalid texture input");
			}
			return ;
		}
	}
	free(line);
	print_errors(game, 1, "Invalid input only 'NO', 'EA', 'WE', 'SO', 'C', 'F',\
		'EN', 'DO' and 'CL' available");
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
	while (line[i] && ft_strchr(" \t\v\f\r", line[i]))
		i++;
	if (line[i] == '\n')
		return (false);
	while (line[i])
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
