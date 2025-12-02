/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:39:53 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 14:40:28 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	hit_loop(t_game *game, int *side)
{
	int	hit;

	hit = 0;
	if (game->meth.sidedistx < game->meth.sidedisty)
	{
		game->meth.sidedistx += game->meth.deltadistx;
		game->meth.mapx += game->meth.stepx;
		*side = 0;
	}
	else
	{
		game->meth.sidedisty += game->meth.deltadisty;
		game->meth.mapy += game->meth.stepy;
		*side = 1;
	}
	if (game->map.grid[game->meth.mapy][game->meth.mapx] == '1')
		hit = 1;
	else if (game->map.grid[game->meth.mapy][game->meth.mapx] == 'd')
	{
		game->meth.door = true;
		hit = 1;
	}
	if (game->map.grid[game->meth.mapy][game->meth.mapx] == 'D')
		game->meth.looking_door = true;
	return (hit);
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
		hit = hit_loop(game, &side);
	}
	return (side);
}
