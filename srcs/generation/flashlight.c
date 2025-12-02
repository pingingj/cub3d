/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:45:48 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 17:12:43 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

/*okay here is another tricky one,softeness is the beam 
		radius and how soft it is gonna be
	ambient is the darkest is gonna be,
		1 is the brigthetest,i use exp to calculate based on
	the distance to the center how far or close to the center is,then i 
	use the distance to the wall,
	and the max reach of the flashlight to calculate how bright again it 
	need to be,
	then i use the ambient that is how dark the defualt world is to 
	calculate using how close to the
	center of the bam and how close to a wall how dark the pixel needs to be,
		aka intenisty then i jsut multyply
	that on the mypixelput color*/
/*circ intensity exp is all squared for a bigger fade,
fist intenisty is becaus eif the same will give 0 os it will stop the ligth beam
the final inteisty math is ambient because thats the default ligth wer only 
adding the other part in brackets its to scale to the max is one*/

static void	ground_light(t_game *game, double max_dist, double *dist_intensity,
		t_point xy)
{
	double	horizon;
	double	screen_dist;

	if (game->player.look < 0)
	{
		horizon = (double)HEIGHT / 2.0 + game->player.look + game->bob;
		if (horizon < -HEIGHT)
			horizon = -HEIGHT;
		if (horizon > HEIGHT * 2)
			horizon = HEIGHT * 2;
		screen_dist = (double)xy.y - horizon;
		if (screen_dist < 0.0)
			screen_dist = 0.0;
		max_dist = 35.0;
		(*dist_intensity) = -(1.0 - (screen_dist / max_dist));
		if ((*dist_intensity) < 0.0)
			(*dist_intensity) = 0.0;
	}
	else
	{
		screen_dist = abs(xy.y - HEIGHT / 2);
		max_dist = 35.0 + game->player.look + game->bob;
		(*dist_intensity) = -(1.0 - (screen_dist / max_dist));
	}
}

static double	ligth_lvl(t_game *game, double circ_intensity, bool is_wall,
		t_point xy)
{
	double	dist_intensity;
	double	max_dist;
	double	intensity;

	max_dist = 0;
	if (is_wall)
	{
		max_dist = 0.0038462 * WIDTH + 5.4615;
		dist_intensity = 1.0 - (game->walldist / max_dist);
		if (dist_intensity < 0.0)
			dist_intensity = 0.0;
	}
	else
		ground_light(game, max_dist, &dist_intensity, xy);
	intensity = AMBIENT + (1.0 - AMBIENT) * circ_intensity * dist_intensity;
	if (intensity < AMBIENT)
		intensity = AMBIENT;
	if (intensity > 1.0)
		intensity = 1.0;
	return (intensity);
}

double	flashlight(int x, int y, t_game *game, bool is_wall)
{
	double	intensity;
	double	circ_intensity;
	double	softness;
	t_pos	d;
	t_point	xy;

	xy.x = x;
	xy.y = y;
	d.x = x - WIDTH / 2;
	d.y = y - HEIGHT / 2;
	softness = WIDTH * 0.15625 + game->player.look / 3 + game->bob / 10.0;
	if (softness < WIDTH * 0.15625 / 3)
		softness = WIDTH * 0.15625 / 3;
	if (((d.x * d.x) + (d.y * d.y)) >= 2.0 * softness * softness)
		return (AMBIENT);
	circ_intensity = 1.0 - (((d.x * d.x) + (d.y * d.y)) / (2.0 * softness
				* softness));
	if (circ_intensity < 0.0)
		circ_intensity = 0.0;
	intensity = ligth_lvl(game, circ_intensity, is_wall, xy);
	return (intensity);
}
