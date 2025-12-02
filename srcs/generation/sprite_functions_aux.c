/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_functions_aux.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:38:06 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 14:25:34 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	sort_dist(int *order, double *sprit_distance, t_game *game)
{
	int		i;
	int		j;
	int		temp_order;
	double	temp_dist;

	i = 0;
	while (i < game->ass.collect_amount - 1)
	{
		j = i + 1;
		while (j < game->ass.collect_amount)
		{
			if (sprit_distance[i] < sprit_distance[j])
			{
				temp_dist = sprit_distance[i];
				sprit_distance[i] = sprit_distance[j];
				sprit_distance[j] = temp_dist;
				temp_order = order[i];
				order[i] = order[j];
				order[j] = temp_order;
			}
			j++;
		}
		i++;
	}
}

void	sprite_text_boundary_check(t_game *game)
{
	if (game->spath.texx < 0)
		game->spath.texx = 0;
	if (game->spath.texx >= game->spath.spt.w)
		game->spath.texx = game->spath.spt.w - 1;
	if (game->spath.texy < 0)
		game->spath.texy = 0;
	if (game->spath.texy >= game->spath.spt.h)
		game->spath.texy = game->spath.spt.h - 1;
}

static double	ligth_lvl_sprite(t_game *game, double sprite_dist,
		double circ_intensity)
{
	double	max_dist;
	double	intensity;
	double	dist_intensity;

	(void)game;
	max_dist = 0.0038462 * WIDTH + 5.4615;
	dist_intensity = 1.0 - (sprite_dist / max_dist);
	if (dist_intensity < 0.0)
		dist_intensity = 0.0;
	intensity = AMBIENT + (1.0 - AMBIENT) * circ_intensity * dist_intensity;
	if (intensity < AMBIENT)
		intensity = AMBIENT;
	if (intensity > 1.0)
		intensity = 1.0;
	return (intensity);
}

double	sprite_flashlight(int x, int y, t_game *game, double sprite_dist)
{
	t_pos	d;
	double	softness;
	double	dist;
	double	circ_intensity;
	double	intensity;

	d.x = x - WIDTH / 2;
	d.y = y - HEIGHT / 2;
	softness = WIDTH * 0.15625 + game->player.look / 3 + game->bob / 10.0;
	if (softness < WIDTH * 0.15625 / 3)
		softness = WIDTH * 0.15625 / 3;
	dist = d.x * d.x + d.y * d.y;
	if (dist >= 2.0 * softness * softness)
		return (AMBIENT);
	circ_intensity = 1.0 - (dist / (2.0 * softness * softness));
	if (circ_intensity < 0.0)
		circ_intensity = 0.0;
	intensity = ligth_lvl_sprite(game, sprite_dist, circ_intensity);
	return (intensity);
}
