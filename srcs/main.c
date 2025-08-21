/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/21 19:32:31 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	print_errors(t_game *game, int error)
{
	(void)game;
	if (error == 1)
		ft_dprintf(2, "Error\nNo file provided");
	if (error == 2)
		ft_dprintf(2, "Error\nFile is not in the correct format");
	if (error == 3)
		ft_dprintf(2, "Error\nNo map provided Bruh\n");
	if (error == 4)
	{
		// free_map(game);
		ft_dprintf(2, "Error\nInvalid Map\n");
	}
	if (error == 5)
	{
		// free_map(game);
		ft_dprintf(2, "Map, is too big\n");
	}
	exit(error);
}
char	**make_maptrix(int row, char *map_file)
{
	char	**maptrix;
	int		i;
	int		fd;

	i = 0;
	fd = open(map_file, O_RDONLY);
	maptrix = malloc(sizeof(char *) * row + 1);
	if (!maptrix)
		return (NULL);
	while (i < row)
	{
		maptrix[i] = get_next_line(fd);
		i++;
	}
	i = 0;
	return (maptrix);
}

int	temp_parse(char *map_file, t_game *game)
{
	int		fd;
	char	*str;
	int		row;

	row = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		str = get_next_line(fd);
		if (str)
			row++;
		else
			break ;
		free(str);
	}
	close(fd);
	game->map = make_maptrix(row, map_file);
	return (1);
}
int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	ft_bzero(&game,sizeof(t_game));
	if (argc == 2)
	{
		// parse(argv[1], fd);
		if (temp_parse(argv[1], &game) < 0)
			return (printf("ERROR\n"));
		ft_matrix_print(game.map);
		game.mlx = mlx_init();
		map_gen(&game);
		mlx_hook(game.win, 17, 0, closex, &game);
		mlx_key_hook(game.win, keys, &game);
		mlx_loop(game.mlx);
		print_errors(&game, 1);
		return (1);
	}
	else
		return (print_errors(&game, 1), 1);
	return (0);
}
