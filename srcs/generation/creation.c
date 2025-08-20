/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:15 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/20 20:01:58 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	background_gen(t_game *game)
{
	game->win = mlx_new_window(game->mlx, 1920, 1080, "NEETs");
	// game->bg_img.img = mlx_new_image(game->mlx, 1920, 1080);
	// game->bg_img.addr = mlx_get_data_addr(game->bg_img.img,
	// 		&game->bg_img.bits_per_pixel, &game->bg_img.line_length,
	// 		&game->bg_img.endian);
	game->mini_map.img = mlx_new_image(game->mlx, 200, 200);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.img,
			&game->mini_map.bits_per_pixel, &game->mini_map.line_length,
			&game->mini_map.endian);
}

static void	player_init(t_game *game)
{
	game->player.posx = 22;
	game->player.posy = 12;
	game->player.dirx = -1;
	game->player.dirx = 0;
	game->player.planey = 0.66;
	game->player.planex = 0;
}
void	math_with_an_e(t_game *game)
{
	int	i;
	int	w;
	int hit;

	hit = 0;
	i = 0;
	w = WIDTH; 
	player_init(game);
	while (i < WIDTH)
	{
		game->meth.camerax = 2 * i / (double)w - 1;
		game->meth.raydirx = game->player.dirx + game->player.planex * game->meth.camerax;
		game->meth.raydiry = game->player.diry + game->player.planey * game->meth.camerax;
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
		if(game->meth.raydirx < 0)
		{
			game->meth.stepx = -1;
			game->meth.sidedistx = (game->player.posx - game->meth.mapx) * game->meth.deltadistx;
		}
		else
		{
			game->meth.stepx = 1;
			game->meth.sidedistx = (game->meth.mapx + 1.0 -game->player.posx) * game->meth.deltadistx;
		}
		if(game->meth.raydiry < 0)
		{
			game->meth.stepy = -1;
			game->meth.sidedisty = (game->player.posy - game->meth.mapy) * game->meth.deltadisty;
		}
		else
		{
			game->meth.stepy = 1;
			game->meth.sidedisty = (game->meth.mapy + 1.0 -game->player.posy) * game->meth.deltadisty;
		}
		while(hit == 0)
		{
			if(game->meth.sidedistx < game->meth.sidedisty)
			{
				
			}
		}
		i++;
	}
}
void	map_gen(t_game *game)
{
	background_gen(game);
	math_with_an_e(game);
}