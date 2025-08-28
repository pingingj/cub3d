/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:37 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/28 14:55:00 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

/*->dir its the direction, like if dirx = 1 & diry = 0, we are looking rigth
  ->plane is a perpendicular vector to the direction, it determines the FOV.

	->camerax indicates how much the ray is leaning to the left/rigth(valors
	go between [-1,1])

	->raydir are the vector that when added will give me the ray,so basicly
		camra x tells me wich side the ray is
  the math to get raydirx/y is basicly connecting the the player the pointy
  part of the triangle
  to the base,using the direction he is looking, the fov,
	and how far left or rigth the ray should be*/

void	setup_ray(t_game *game, int x)
{
	game->meth.camerax = 2 * x / (double)WIDTH - 1;
	game->meth.raydirx = game->player.dirx + game->player.planex
		* game->meth.camerax;
	game->meth.raydiry = game->player.diry + game->player.planey
		* game->meth.camerax;
	game->meth.mapx = (int)game->player.posx;
	game->meth.mapy = (int)game->player.posy;
}

void	math_with_an_e(t_game *game)
{
	double	walldist;
	int		sdraw;
	int		edraw;
	int		i;

	i = 0;
	game->meth.looking_door = false;
	while (i < WIDTH)
	{
		setup_ray(game, i);
		dda_prep(game);
		game->meth.orientation = hit_wall(game);
		if(game->meth.door == true)
			game->meth.looking_door = true;
		walldist = calc_wall_dist(game);
		wall_size(game, walldist, &sdraw, &edraw);
		artistic_moment(game, i, sdraw, edraw);
		i++;
	}
	
}

void	create_frame(t_game *game)
{
	math_with_an_e(game);
	// draw_minimap(game);
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
	// mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20,
	// 20);
}
