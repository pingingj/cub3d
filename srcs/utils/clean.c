/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finn <finn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:55:00 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/27 16:10:10 by finn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	bazooka_imgs(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->ass.textures[i].img)
			mlx_destroy_image(game->mlx, game->ass.textures[i].img);
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (game->nums[i].img)
			mlx_destroy_image(game->mlx, game->nums[i].img);
		i++;
	}
	i = 0;
	while (i < 194)
	{
		if (game->title[i].img)
			mlx_destroy_image(game->mlx, game->title[i].img);
		i++;
	}
}

void	closex2(t_game *game)
{
	bazooka_imgs(game);
	if (game->bg_img.img)
		mlx_destroy_image(game->mlx, game->bg_img.img);
	while (game->doors_opened != NULL)
		free_doors(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game(game);
}

int	closex(t_game *game)
{
	ft_printf("\n\nGAME CLOSING\n");
	if (game->ass.door.texture.img)
		mlx_destroy_image(game->mlx, game->ass.door.texture.img);
	if (game->ass.enemy.texture.img)
		mlx_destroy_image(game->mlx, game->ass.enemy.texture.img);
	if (game->ass.barrel.img)
		mlx_destroy_image(game->mlx, game->ass.barrel.img);
	if (game->ass.death_screen.img)
		mlx_destroy_image(game->mlx, game->ass.death_screen.img);
	if (game->ass.win_screen.img)
		mlx_destroy_image(game->mlx, game->ass.win_screen.img);
	if (game->ass.pause_screen.img)
		mlx_destroy_image(game->mlx, game->ass.pause_screen.img);
	if (game->slash.img)
		mlx_destroy_image(game->mlx, game->slash.img);
	closex2(game);
	exit(0);
}

// void	print_info(t_game game)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
	// printf("NO = %s\n", game.ass.textures[NO].filename);
	// printf("EA = %s\n", game.ass.textures[EA].filename);
	// printf("SO = %s\n", game.ass.textures[SO].filename);
	// printf("WE = %s\n", game.ass.textures[WE].filename);
	// printf("CL = %s\n", game.ass.textures[CL].filename);
	// printf("EN = %s\n", game.ass.textures[EN].filename);
	// printf("DO = %s\n", game.ass.textures[DO].filename);
	// printf("length = %f\n", game.map.pos.x);
	// printf("height = %f\n", game.map.pos.y);
	// printf("collect amount  = %d\n", game.ass.collect_amount - 1);
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
	// printf("player cords x = %f y = %f\n", game.player.posx, 
	//game.player.posy);
	// printf("collected amount = %d\n", game.collected_comics);
// 	while (i < game.map.pos.y)
// 	{
// 		j = 0;
// 		while (j <= game.map.pos.x)
// 		{
// 			if (game.map.grid[i][j] == ' ')
// 				ft_printf("v");
// 			else if (game.map.grid[i][j] == '1')
// 				ft_printf("1");
// 			else if (game.map.grid[i][j] == 'o')
// 				ft_printf("o");
// 			else if (game.map.grid[i][j] == 'd')
// 				ft_printf("d");
// 			else if (game.map.grid[i][j] == 'c')
// 				ft_printf("c");
// 			else if (game.map.grid[i][j] == 'j')
// 				ft_printf("j");
// 			else if (game.map.grid[i][j] == '\0')
// 				ft_printf("\n");
// 			j++;
// 		}
// 		i++;
// 	}
// }

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
