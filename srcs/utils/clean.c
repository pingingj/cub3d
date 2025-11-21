/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:55:00 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/21 18:11:49 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	closex2(t_game *mlx)
{
	int	i;

	i = 0;
	while (i < 194)
	{
		if (mlx->title[i].img)
			mlx_destroy_image(mlx->mlx, mlx->title[i].img);
		i++;
	}
	if (mlx->bg_img.img)
		mlx_destroy_image(mlx->mlx, mlx->bg_img.img);
	free(mlx->move);
	while(mlx->doors_opened != NULL)
		free_doors(mlx);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_game(mlx);
}

int	closex(t_game *mlx)
{
	int	i;

	i = 0;
	ft_printf("\n\nGAME CLOSING\n");
	if (mlx->ass.door.texture.img)
		mlx_destroy_image(mlx->mlx, mlx->ass.door.texture.img);
	if (mlx->ass.enemy.texture.img)
		mlx_destroy_image(mlx->mlx, mlx->ass.enemy.texture.img);
	if (mlx->ass.barrel.img)
		mlx_destroy_image(mlx->mlx, mlx->ass.barrel.img);
	if (mlx->ass.death_screen.img)
		mlx_destroy_image(mlx->mlx, mlx->ass.death_screen.img);
	if (mlx->ass.win_screen.img)
		mlx_destroy_image(mlx->mlx, mlx->ass.win_screen.img);
	if (mlx->ass.pause_screen.img)
		mlx_destroy_image(mlx->mlx, mlx->ass.pause_screen.img);
	while (i < 6)
	{
		if (mlx->ass.textures[i].img)
			mlx_destroy_image(mlx->mlx, mlx->ass.textures[i].img);
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (mlx->nums[i].img)
			mlx_destroy_image(mlx->mlx, mlx->nums[i].img);
		i++;
	}
	closex2(mlx);
	exit(0);
}

void	print_info(t_game game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	printf("NO = %s\n", game.ass.textures[NO].filename);
	printf("EA = %s\n", game.ass.textures[EA].filename);
	printf("SO = %s\n", game.ass.textures[SO].filename);
	printf("WE = %s\n", game.ass.textures[WE].filename);
	printf("CL = %s\n", game.ass.textures[CL].filename);
	printf("EN = %s\n", game.ass.textures[EN].filename);
	printf("DO = %s\n", game.ass.textures[DO].filename);
	printf("length = %f\n", game.map.pos.x);
	printf("height = %f\n", game.map.pos.y);
	printf("collect amount  = %d\n", game.ass.collect_amount - 1);
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
	printf("collected amount = %d\n", game.collected_comics);
	while (i < game.map.pos.y)
	{
		j = 0;
		while (j <= game.map.pos.x)
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
			else if (game.map.grid[i][j] == 'j')
				ft_printf("j");
			else if (game.map.grid[i][j] == '\0')
				ft_printf("\n");
			j++;
		}
		i++;
	}
	i = 0;
	// while(i < game.ass.collect_amount)
	// {
	// 	printf("sprites cords x = %f y = %f\n", game.ass.sprites[i].cords.x,
			// game.ass.sprites->cords.y);
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
	if (game->ass.sprites)
		free(game->ass.sprites);
	if (game->ass.ceiling.nums)
		free(game->ass.ceiling.nums);
	if (game->ass.floor.nums)
		free(game->ass.floor.nums);
	if (game->map.grid)
		freetrix(game->map.grid);
	if (game->visited)
		freeany(game->visited);
	if (game->prev)
		freeany(game->prev);
	while (i < 7)
	{
		if (game->ass.textures[i].filename)
			free(game->ass.textures[i].filename);
		i++;
	}
}

/// @brief Printing errors of program
/// @param game struct to free
/// @param error if error = 1 it will free game struct
/// @param msg msg to print
void	print_errors(t_game *game, int error, char *msg)
{
	if (game->fd > 2)
		close(game->fd);
	if (msg != NULL)
		ft_dprintf(2, "Error\n%s\n", msg);
	if (error == 1)
		free_game(game);
	exit(error);
}
