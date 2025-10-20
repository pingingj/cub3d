/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:37 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/20 14:35:35 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

/*->dir its the direction, like if dirx = 1 & diry = 0, we are looking rigth
  ->plane is a perpendicular vector to the direction, it determines the FOV.

	->camerax indicates how much the ray is leaning to the left/rigth(valors
	go between [-1,1])

	->raydir are the vector that when added will give me the ray,so basicly
		camra x tells me wich side the ray is
  the math to get raydirx/y is basicly connecting the player the pointy
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
	int	sdraw;
	int	edraw;
	int	i;

	i = 0;
	game->meth.looking_door = false;
	while (i < WIDTH)
	{
		setup_ray(game, i);
		dda_prep(game);
		game->meth.orientation = hit_wall(game);
		if (game->meth.door == true)
			game->meth.looking_door = true;
		game->walldist = calc_wall_dist(game);
		game->wall_dist_sp[i] = game->walldist;
		wall_size(game, game->walldist, &sdraw, &edraw);
		artistic_moment(game, i, sdraw, edraw);
		i++;
	}
	if(game->ass.collect_amount > 0)
		hande_sprites(game);
}

void	create_frame(t_game *game)
{
	// static int bob_flag;
	// if (bob_flag == 0)
	// {
	// 	game->bob += 2;
	// 	if(game->bob > 6)
	// 		bob_flag = 1;
	// }
	// else
	// {
	// 	game->bob -= 2;
	// 	if(game->bob < -6)
	// 		bob_flag = 0;
	// }
	math_with_an_e(game);
	mlx_clear_window(game->mlx, game->win);
	if (game->mini.show == true)
		draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}
