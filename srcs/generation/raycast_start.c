/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:37 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/17 14:00:54 by dpaes-so         ###   ########.fr       */
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

double	sprite_flashlight(int x, int y, t_game *game, double sprite_dist)
{
	double	dx;
	double	dy;
	double	softness;
	double	dist;
	double	circ_intensity;
	double	max_dist;
	double	dist_intensity;
	double	intensity;
	double 	max_dist_sq;

	dx = x - WIDTH / 2;
	dy = y - HEIGHT / 2;
	softness = 300.0 + game->player.look / 10.0;
	if (softness < 80.0)
		softness = 80.0;
	dist = dx * dx + dy * dy;
	max_dist_sq = 2.0 * softness * softness;
	if (dist >= max_dist_sq)
		return (AMBIENT);
	circ_intensity = 1.0 - (dist / (2.0 * softness * softness));
	if (circ_intensity < 0.0)
		circ_intensity = 0.0;
	max_dist = 15.0 - game->bob / 10.0;
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

void	hande_sprites(t_game *game)
{
	int		i;
	int		order[game->ass.collect_amount];
	double	mathx;
	double	mathy;
	double	transformx;
	double	transformy;
	double	sprite_dist[game->ass.collect_amount];
	double	inverse;
	double	spritexlocation;
	double	sprite_height;
	double	sprite_width;
	int		sdrawx;
	int		sdrawy;
	int		edrawx;
	int		edrawy;
	int		sp_index;
	int		texx;
	int		screen_center;
	int		py;
	int		d;
	int		texy;
	int		color;
	double	intensity;

	i = -1;
	while (++i < game->ass.collect_amount)
	{
		order[i] = i;
		mathx = game->player.posx - game->ass.sprites[i].cords.x;
		mathy = game->player.posy - game->ass.sprites[i].cords.y;
		sprite_dist[i] = mathx * mathx + mathy * mathy;
	}
	i = -1;
	sort_dist(order, sprite_dist, game);
	while (++i < game->ass.collect_amount)
	{
		if (game->ass.sprites[order[i]].exists == false)
			continue ;
		mathx = game->ass.sprites[order[i]].cords.x - game->player.posx;
		mathy = game->ass.sprites[order[i]].cords.y - game->player.posy;
		inverse = 1.0 / (game->player.planex * game->player.diry
				- game->player.dirx * game->player.planey);
		transformx = inverse * (game->player.diry * mathx - game->player.dirx
				* mathy);
		transformy = inverse * (-game->player.planey * mathx
				+ game->player.planex * mathy);
		spritexlocation = (WIDTH / 2) * (1 + transformx / transformy);
		sprite_height = fabs(HEIGHT / transformy);
		screen_center = HEIGHT / 2 + game->player.look;
		sdrawy = screen_center - sprite_height / 2;
		edrawy = screen_center + sprite_height / 2;
		sprite_width = fabs(HEIGHT / transformy);
		sdrawx = -sprite_width / 2 + spritexlocation;
		edrawx = sprite_width / 2 + spritexlocation;
		if (sdrawx < 0)
			sdrawx = 0;
		if (edrawx >= WIDTH)
			edrawx = WIDTH - 1;
		if (sdrawy < 0)
			sdrawy = 0;
		if (edrawy >= HEIGHT)
			edrawy = HEIGHT - 1;
		sp_index = sdrawx;
		while (sp_index < edrawx)
		{
			texx = (int)(256 * (sp_index - (-sprite_width / 2
							+ spritexlocation)) * game->ass.barrel.w
					/ sprite_width) / 256;
			if (transformy > 0 && sp_index >= 0 && sp_index < WIDTH
				&& transformy < game->wall_dist_sp[sp_index] + 0.6)
			{
				py = sdrawy;
				while (py < edrawy)
				{
					d = (py - screen_center + sprite_height / 2) * 256;
					texy = ((d * game->ass.barrel.h) / sprite_height) / 256;
					if (texx < 0)
						texx = 0;
					if (texx >= game->ass.barrel.w)
						texx = game->ass.barrel.w - 1;
					if (texy < 0)
						texy = 0;
					if (texy >= game->ass.barrel.h)
						texy = game->ass.barrel.h - 1;
					color = pixel_get(&game->ass.barrel, texx, texy);
					if ((unsigned int)color != 0xFF000000)
					{
						intensity = sprite_flashlight(sp_index, py, game,
								transformy);
						if (game->laggy_lanter)
							my_mlx_pixel_put(&game->bg_img, sp_index, py,
								add_light(color, intensity));
						else
							my_mlx_pixel_put(&game->bg_img, sp_index, py,
								color);
					}
					py++;
				}
			}
			sp_index++;
		}
	}
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
