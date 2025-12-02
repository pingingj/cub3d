/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:38:08 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 14:40:12 by dpaes-so         ###   ########.fr       */
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

/*->so here, if raydir is 0 means we are following the x/y axes,
	and since we cant divide by 0 we just slap a big ahh number
   cuz point the square of our grid is 1 by 1,and we are calculating how far we
   need to go to reach the other line
   (vertical on raydirx other way around on y) we use fabs because it cant be
   negative since its a distance
   ->so deltacalculates how far each square is from eachother following the
   ray,
	sidedis calculates how far the player is
   from the closes line,
	since the player can be in a lot of diferent places in the same square
	since we use floats to walk around
	->step is just the directions the ray is going*/
void	prepare_dda_start(t_game *game)
{
	if (game->meth.raydirx == 0)
		game->meth.deltadistx = 1e30;
	else
		game->meth.deltadistx = fabs(1 / game->meth.raydirx);
	if (game->meth.raydiry == 0)
		game->meth.deltadisty = 1e30;
	else
		game->meth.deltadisty = fabs(1 / game->meth.raydiry);
}

void	dda_prep(t_game *game)
{
	prepare_dda_start(game);
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
}

/*this is jsut becayse the DDA walks one square 2 much so we gotta go back
one square to get the real distance*/
double	calc_wall_dist(t_game *game)
{
	if (game->meth.orientation == 0)
		return (game->meth.sidedistx - game->meth.deltadistx);
	else
		return (game->meth.sidedisty - game->meth.deltadisty);
}

void	wall_size(t_game *game, double walldist, int *sdraw, int *edraw)
{
	int	add;

	add = 0;
	add += game->player.look + game->bob;
	if (walldist <= 0.000001)
		walldist = 0.000001;
	game->meth.line_height = (int)(HEIGHT / walldist);
	(*sdraw) = HEIGHT / 2 - game->meth.line_height / 2 + add ;
	if ((*sdraw) < 0)
		(*sdraw) = 0;
	(*edraw) = HEIGHT / 2 + game->meth.line_height / 2 + add ;
	if ((*edraw) < 0)
		(*edraw) = 0;
}
