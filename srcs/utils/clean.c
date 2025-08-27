/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:55:00 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/27 17:40:01 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	closex(t_game *mlx)
{
	ft_printf("\n\nGAME CLOSING\n");
	mlx_destroy_image(mlx->mlx, mlx->bg_img.img);
	free_game(mlx);
	free(mlx->move);
	mlx_destroy_image(mlx->mlx, mlx->mini_map.img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

void	print_info(t_game game)
{
	int	i;

	i = 0;
	printf("NO = %s\n", game.ass.walls[NO].filename);
	printf("EA = %s\n", game.ass.walls[EA].filename);
	printf("SO = %s\n", game.ass.walls[SO].filename);
	printf("WE = %s\n", game.ass.walls[WE].filename);
	printf("Ceiling = %s\n", game.ass.ceiling.nums);
	printf("R = %d\n", game.ass.ceiling.red);
	printf("G = %d\n", game.ass.ceiling.green);
	printf("B = %d\n", game.ass.ceiling.blue);
	printf("Floor = %s\n", game.ass.floor.nums);
	printf("R = %d\n", game.ass.floor.red);
	printf("G = %d\n", game.ass.floor.green);
	printf("B = %d\n", game.ass.floor.blue);
	printf("hexa ceiling = %d\n", game.ass.ceiling.hexa);
	printf("hexa floor = %d\n", game.ass.floor.hexa);
	printf("player cords x = %f y = %f\n", game.player.posx, game.player.posy);
	while (i < game.map.pos.y)
	{
		ft_printf("%s", game.map.grid[i]);
		i++;
	}
	// ft_printf("PLAYER positions X = %d, Y = %d\n", map.player.pos.x,
	// 	map.player.pos.y);
	// ft_printf("COLLETIBLE AMOUNT = %d\n", map.c_amount);
	// ft_printf("EXIT position: X = %d, Y = %d\n",
	// 	map.exit.pos.x, map.exit.pos.y);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
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

void	print_errors(t_game *game, int error, char *msg, int fd)
{
	if (fd > 0)
		close(fd);
	ft_dprintf(2, "Error\n%s\n", msg);
	if (error == 1)
		free_game(game);
	exit(error);
}
