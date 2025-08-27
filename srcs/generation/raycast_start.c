/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:37 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/26 19:54:46 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

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
	while (i < WIDTH)
	{
		setup_ray(game, i);
		dda_prep(game);
		game->meth.orientation = hit_wall(game);
		walldist = calc_wall_dist(game);
		wall_size(game, walldist, &sdraw, &edraw);
		artistic_moment(game, i, sdraw, edraw);
		i++;
	}
}
