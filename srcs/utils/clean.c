/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:55:00 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/09 15:47:18 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	closex(t_game *mlx)
{
	ft_printf("\n\nGAME CLOSING\n");
	mlx_destroy_image(mlx->mlx, mlx->ass.barrel.img);
	mlx_destroy_image(mlx->mlx, mlx->bg_img.img);
	free(mlx->move);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_game(mlx);
	exit(0);
}

void	print_info(t_game game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	// printf("NO = %s\n", game.ass.walls[NO].filename);
	// printf("EA = %s\n", game.ass.walls[EA].filename);
	// printf("SO = %s\n", game.ass.walls[SO].filename);
	// printf("WE = %s\n", game.ass.walls[WE].filename);
	printf("length = %f\n", game.map.pos.x);
	printf("height = %f\n", game.map.pos.y);
	// printf("Ceiling = %s\n", game.ass.ceiling.nums);
	// printf("R = %d\n", game.ass.ceiling.red);
	// printf("G = %d\n", game.ass.ceiling.green);
	// printf("B = %d\n", game.ass.ceiling.blue);
	// printf("Floor = %s\n", game.ass.floor.nums);
	// printf("R = %d\n", game.ass.floor.red);
	// printf("G = %d\n", game.ass.floor.green);
	// printf("B = %d\n", game.ass.floor.blue);
	// printf("hexa ceiling = %d\n", game.ass.ceiling.hexa);
	// printf("hexa floor = %d\n", game.ass.floor.hexa);
	printf("player cords x = %f y = %f\n", game.player.posx, game.player.posy);
	while (i < game.map.pos.y)
	{
		j = 0;
		while(j <= game.map.pos.x)
		{
			if (game.map.grid[i][j] == ' ')
				ft_printf("v");
			else if (game.map.grid[i][j] == '1')
				ft_printf("1");
			else if (game.map.grid[i][j] == 'o')
				ft_printf("o");
			else if (game.map.grid[i][j] == 'd')
				ft_printf("d");
			else if (game.map.grid[i][j] == 'c')
				ft_printf("c");
			else if (game.map.grid[i][j] == '\0')
				ft_printf("\n");
			j++;
		}
		i++;
	}
	i = 0;
	// while(i < game.ass.collect_amount)
	// {
	// 	printf("collectible cords x = %f y = %f\n", game.ass.collectible[i].cords.x, game.ass.collectible->cords.y);
	// 	i++;
	// }
	// ft_printf("COLLETIBLE AMOUNT = %d\n", game.c_amount);
	// ft_printf("EXIT position: X = %d, Y = %d\n",
	// 	map.exit.pos.x, map.exit.pos.y);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->ass.collectible)
		free(game->ass.collectible);
	if (game->ass.ceiling.nums)
		free(game->ass.ceiling.nums);
	if (game->ass.floor.nums)
		free(game->ass.floor.nums);
	if (game->map.grid)
		freetrix(game->map.grid);
	while (i < 4)
	{
		if (game->ass.walls[i].filename)
			free(game->ass.walls[i].filename);
		i++;
	}
}

/// @brief Printing errors of program
/// @param game struct to free
/// @param error if error = 1 it will free game struct
/// @param msg msg to print
/// @param fd closes open fd send -1 if no fd needs to be closed
void	print_errors(t_game *game, int error, char *msg, int fd)
{
	if (fd > 2)
		close(fd);
	ft_dprintf(2, "Error\n%s\n", msg);
	if (error == 1)
		free_game(game);
	exit(error);
}
