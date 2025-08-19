/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/19 14:25:19 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	print_errors(t_game *game, int error)
{
	if (error == 1)
		ft_dprintf(2, "Error\nNo file provided");
	if (error == 2)
		ft_dprintf(2, "Error\nFile is not in the correct format");
	if (error == 3)
		ft_dprintf(2, "Error\nNo map provided Bruh\n");
	if (error == 4)
	{
		free_map(game);
		ft_dprintf(2, "Error\nInvalid Map\n");
	}
	if (error == 5)
	{
		free_map(game);
		ft_dprintf(2, "Map, is too big\n");
	}
	exit(error);
}

// fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 		print_errors(&game, )

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (argc != 2)
	{
		print_errors(&game, 1);
		return (1);
	}
	parse(argv[1], fd);
	return (0);
}