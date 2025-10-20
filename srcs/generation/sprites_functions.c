/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:37:27 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/20 14:08:32 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_sprite(t_game *game)
{
	game->spath.d = (game->spath.py - game->spath.screen_center
			+ game->spath.sprite_height / 2) * 256;
	game->spath.texy = ((game->spath.d * game->spath.spt.h)
			/ game->spath.sprite_height) / 256;
	sprite_text_boundary_check(game);
	game->spath.color = pixel_get(&game->spath.spt, game->spath.texx,
			game->spath.texy);
	if ((unsigned int)game->spath.color != 0x000000)
	{
		game->spath.intensity = sprite_flashlight(game->spath.sp_index,
				game->spath.py, game, game->spath.transformy);
		if (game->laggy_lanter)
			my_mlx_pixel_put(&game->bg_img, game->spath.sp_index,
				game->spath.py, add_light(game->spath.color,
					game->spath.intensity));
		else
			my_mlx_pixel_put(&game->bg_img, game->spath.sp_index,
				game->spath.py, game->spath.color);
	}
	game->spath.py++;
}

void	draw_sprite_prep(t_game *game)
{
	game->spath.texx = (int)(256 * (game->spath.sp_index
				- (-game->spath.sprite_width / 2 + game->spath.spritexlocation))
			* game->spath.spt.w / game->spath.sprite_width) / 256;
	if (game->spath.transformy > 0 && game->spath.sp_index >= 0
		&& game->spath.sp_index < WIDTH
		&& game->spath.transformy < game->wall_dist_sp[game->spath.sp_index]
		+ 0.6)
	{
		game->spath.py = game->spath.sdrawy;
		while (game->spath.py < game->spath.edrawy)
			draw_sprite(game);
	}
	game->spath.sp_index++;
}

void	sprite_math(t_game *game, int *order)
{
	game->spath.mathx = game->ass.sprites[order[game->spath.i]].cords.x
		- game->player.posx;
	game->spath.mathy = game->ass.sprites[order[game->spath.i]].cords.y
		- game->player.posy;
	game->spath.inverse = 1.0 / (game->player.planex * game->player.diry
			- game->player.dirx * game->player.planey);
	game->spath.transformx = game->spath.inverse * (game->player.diry
			* game->spath.mathx - game->player.dirx * game->spath.mathy);
	game->spath.transformy = game->spath.inverse * (-game->player.planey
			* game->spath.mathx + game->player.planex * game->spath.mathy);
	game->spath.spritexlocation = (WIDTH / 2) * (1 + game->spath.transformx
			/ game->spath.transformy);
	game->spath.sprite_height = fabs(HEIGHT / game->spath.transformy);
	game->spath.screen_center = HEIGHT / 2 + game->player.look;
	game->spath.sdrawy = game->spath.screen_center - game->spath.sprite_height
		/ 2;
	game->spath.edrawy = game->spath.screen_center + game->spath.sprite_height
		/ 2;
	game->spath.sprite_width = fabs(HEIGHT / game->spath.transformy);
	game->spath.sdrawx = -game->spath.sprite_width / 2
		+ game->spath.spritexlocation;
	game->spath.edrawx = game->spath.sprite_width / 2
		+ game->spath.spritexlocation;
}

void	start_sprite_handle(t_game *game, int *order)
{
	if (game->ass.sprites[order[game->spath.i]].enemy == true)
		game->spath.spt = game->ass.enemy.texture;
	else
		game->spath.spt = game->ass.textures[CL];
	sprite_math(game, order);
	if (game->spath.sdrawx < 0)
		game->spath.sdrawx = 0;
	if (game->spath.edrawx >= WIDTH)
		game->spath.edrawx = WIDTH - 1;
	if (game->spath.sdrawy < 0)
		game->spath.sdrawy = 0;
	if (game->spath.edrawy >= HEIGHT)
		game->spath.edrawy = HEIGHT - 1;
	game->spath.sp_index = game->spath.sdrawx;
	while (game->spath.sp_index < game->spath.edrawx)
		draw_sprite_prep(game);
}
void	hande_sprites(t_game *game)
{
	int order[game->ass.collect_amount];
	double sprite_dist[game->ass.collect_amount];

	game->spath.i = -1;
	while (++game->spath.i < game->ass.collect_amount)
	{
		order[game->spath.i] = game->spath.i;
		game->spath.mathx = game->player.posx
			- game->ass.sprites[game->spath.i].cords.x;
		game->spath.mathy = game->player.posy
			- game->ass.sprites[game->spath.i].cords.y;
		sprite_dist[game->spath.i] = game->spath.mathx * game->spath.mathx
			+ game->spath.mathy * game->spath.mathy;
	}
	game->spath.i = -1;
	sort_dist(order, sprite_dist, game);
	while (++game->spath.i < game->ass.collect_amount)
	{
		if (game->ass.sprites[order[game->spath.i]].exists == false)
			continue ;
		start_sprite_handle(game, order);
	}
}