/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:38:08 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/09/25 10:59:42 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

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
/*->hit wall we calculate how far the ray goes until it hits a wall,
	so we need to add the distance the player need to reach the closes wall
   then we just nned to add delta,because its the distance the ray walsk to
   go from one line to another lane in the same orientation(x or y)
  ->we add on the map side,
	because we need to "walk" on the map to be able to identify the wall*/

int	hit_wall(t_game *game)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	game->meth.door = false;
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
		if (game->map.grid[game->meth.mapy][game->meth.mapx] == '1')
			hit = 1;
		else if (game->map.grid[game->meth.mapy][game->meth.mapx] == 'd')
		{
			game->meth.door = true;
			hit = 1;
		}
		if(game->map.grid[game->meth.mapy][game->meth.mapx] == 'D')
			game->meth.looking_door = true;
	}
	return (side);
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
	int	line_heigth;
	int add;

	add = 0;
	if(game->player.sneak != 0)
		add = game->player.sneak;
	add +=game->player.look;
	(void)game;
	if (walldist <= 0.000001)
		walldist = 0.000001;
	line_heigth = (int)(HEIGHT / walldist);
	(*sdraw) = HEIGHT / 2 - line_heigth / 2 + add;
	if ((*sdraw) < 0)
		(*sdraw) = 0;
	(*edraw) = HEIGHT / 2 + line_heigth / 2 + add;
	if ((*edraw) < 0)
		(*edraw) = 0;
}
