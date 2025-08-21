/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:15 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/21 19:32:54 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	background_gen(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "NEETs");
	game->bg_img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->bg_img.addr = mlx_get_data_addr(game->bg_img.img,
			&game->bg_img.bits_per_pixel, &game->bg_img.line_length,
			&game->bg_img.endian);
	// game->mini_map.img = mlx_new_image(game->mlx, 200, 200);
	// game->mini_map.addr = mlx_get_data_addr(game->mini_map.img,
	// 		&game->mini_map.bits_per_pixel, &game->mini_map.line_length,
	// 		&game->mini_map.endian);
}

static void	player_init(t_game *game)
{
	game->player.posx = 5.5;
	game->player.posy = 7.5;
	game->player.dirx = 0;
	game->player.diry = -1;
	game->player.planey = 0;
	game->player.planex = 0.66;
}

int	hit_wall(t_game *game)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (game->meth.sidedistx < game->meth.sidedisty)
		{
			game->meth.sidedistx += game->meth.deltadistx;
			game->meth.mapx += game->meth.stepx;
			side = 0;
		}
		else
		{
			game->meth.sidedisty += game->meth.deltadisty;
			game->meth.mapy += game->meth.stepy;
			side = 1;
		}
		if (game->map[game->meth.mapy][game->meth.mapx] >= '1')
			hit = 1;
	}
	return (side);
}

void	wall_size(t_game *game, double walldist, int *sdraw, int *edraw)
{
	int	line_heigth;

	(void)game;
	if (walldist <= 0.000001)
		walldist = 0.000001;
	line_heigth = (int)(HEIGHT / walldist);
	(*sdraw) = -line_heigth / 2 + HEIGHT / 2;
	if ((*sdraw) < 0)
		(*sdraw) = 0;
	(*edraw) = line_heigth / 2 + HEIGHT / 2;
	if ((*edraw) < 0)
		(*edraw) = 0;
}

void	artistic_moment(t_game *game, int x, int sdraw, int edraw)
{
	int	color;
	int	ceiling;
	int	floor;
	int	y;

	ceiling = 0x0000FF;
	floor = 0xFFA500;
	y = 0;
	if (game->meth.orientation == 0)
		color = 0xFF0000;
	else
		color = 0x880000;
	while (y < HEIGHT)
	{
		if (y < sdraw)
			my_mlx_pixel_put(&game->bg_img, x, y, ceiling);
		else if (y >= sdraw && y <= edraw)
			my_mlx_pixel_put(&game->bg_img, x, y, color);
		else
			my_mlx_pixel_put(&game->bg_img, x, y, floor);
		y++;
	}
}
void	math_with_an_e(t_game *game)
{
	int		i;
	int		w;
	double	walldist;
	int		sdraw;
	int		edraw;

	i = 0;
	w = WIDTH;
	while (i < WIDTH)
	{
		game->meth.camerax = 2 * i / (double)w - 1;
		game->meth.raydirx = game->player.dirx + game->player.planex
			* game->meth.camerax;
		game->meth.raydiry = game->player.diry + game->player.planey
			* game->meth.camerax;
		game->meth.mapx = (int)game->player.posx;
		game->meth.mapy = (int)game->player.posy;
		if (game->meth.raydirx == 0)
			game->meth.deltadistx = 1e30;
		else
			game->meth.deltadistx = fabs(1 / game->meth.raydirx);
		if (game->meth.raydiry == 0)
			game->meth.deltadisty = 1e30;
		else
			game->meth.deltadisty = fabs(1 / game->meth.raydiry);
		if (game->meth.raydirx < 0)
		{
			game->meth.stepx = -1;
			game->meth.sidedistx = (game->player.posx - game->meth.mapx)
				* game->meth.deltadistx;
		}
		else
		{
			game->meth.stepx = 1;
			game->meth.sidedistx = (game->meth.mapx + 1.0 - game->player.posx)
				* game->meth.deltadistx;
		}
		if (game->meth.raydiry < 0)
		{
			game->meth.stepy = -1;
			game->meth.sidedisty = (game->player.posy - game->meth.mapy)
				* game->meth.deltadisty;
		}
		else
		{
			game->meth.stepy = 1;
			game->meth.sidedisty = (game->meth.mapy + 1.0 - game->player.posy)
				* game->meth.deltadisty;
		}
		game->meth.orientation = hit_wall(game);
		if (game->meth.orientation == 0)
			walldist = game->meth.sidedistx - game->meth.deltadistx;
		else
			walldist = game->meth.sidedisty - game->meth.deltadisty;
		wall_size(game, walldist, &sdraw, &edraw);
		artistic_moment(game, i, sdraw, edraw);
		i++;
	}
}
void	map_gen(t_game *game)
{
	player_init(game);
	background_gen(game);
	math_with_an_e(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}