/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/19 15:06:21 by dpaes-so         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	if (argc != 2)
	{
		print_errors(&game, 1);
		return (1);
	}
	// parse(argv[1], fd);
	game.mlx = mlx_init();
	map_gen(&game);
	mlx_hook(game.win, 17, 0, closex, &game);
    mlx_key_hook(game.win,keys,&game);
	mlx_loop(game.mlx);
	return (0);
}
