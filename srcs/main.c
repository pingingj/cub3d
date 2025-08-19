/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/19 18:50:56 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	print_errors(t_game *game, int error)
{
	(void)game;
	if (error == 1)
		ft_dprintf(2, "Error\nInvalid file or no file provided\n");
	if (error == 2)
		ft_dprintf(2, "Error\nFile is not in the correct format\n");
	if (error == 3)
		ft_dprintf(2, "Error\nEmpty File\n");
	if (error == 4)
	{
		// free_map(game);
		ft_dprintf(2, "Error\nInvalid texture\n");
	}
	if (error == 5)
	{
		// free_map(game);
		ft_dprintf(2, "Map is too big\n");
	}
	exit(error);
}

bool	check_texture(char *line, t_game *game, char dir)
{
	int	i;

	i = 0;
	if (dir == 'C' || dir == 'F')
		line += 1;
	else
		line += 2;
	skip_wspaces(&line);
	if ((ft_strstr(line, ".xpm") == NULL || line[0] == '\0') && (dir != 'C' || dir != 'F'))
		return (false);
	while(line[i] != '\0' && line[i] != ' ' && (line[i] < 9 || line[i] > 13))
		i++;
	skip_wspaces(&line);
	if (line[i] && line[i] != '\n')
		return (false);
	if (dir == 'N')
		game->ass.NO.filename = ft_strdup(line);
	else if (dir == 'E')
		game->ass.EA.filename = ft_strdup(line);
	else if (dir == 'W')
		game->ass.WE.filename = ft_strdup(line);
	else if (dir == 'S')
		game->ass.SO.filename = ft_strdup(line);
	else if (dir == 'C')
		game->ass.ceiling = ft_strdup(line);
	else if (dir == 'F')
		game->ass.floor = ft_strdup(line);
	return (true);
}

bool	check_line(char *line, t_game *game)
{
	if (line[0] && line[0] == '\n')
		return (true);
	skip_wspaces(&line);
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (check_texture(line, game, 'N') == false)
			return (false);		
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (check_texture(line, game, 'E') == false)
			return (false);		
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (check_texture(line, game, 'W') == false)
			return (false);		
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (check_texture(line, game, 'S') == false)
			return (false);		
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (check_texture(line, game, 'C') == false)
			return (false);		
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (check_texture(line, game, 'F') == false)
			return (false);		
	}
	else
		return (print_errors(game, 4), false);
	return (true);
}

bool	get_textures(char *filename, t_game *game, int fd)
{
	char	*temp;

	(void)filename;
	temp = get_next_line(fd);
	if (temp == NULL)
	{
		print_errors(game, 3);
		return (false);
	}
	while (temp != NULL)
	{
		if (check_line(temp, game) == false)
			return (false);
		free(temp);
		temp = get_next_line(fd);
	}
	return (true);
}

bool	parse(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_errors(game, 1);
		return (false);
	}
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
	{
		print_errors(game, 2);
		close(fd);
		return (false);
	}
	if (get_textures(filename, game, fd) == false)
	{
		close(fd);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_errors(&game, 1);
		return (1);
	}
	if (parse(argv[1], &game) == false)
		return (1);
	printf("we made it\n");
	return (0);
}