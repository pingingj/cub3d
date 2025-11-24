/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:37 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/21 19:17:12 by dgarcez-         ###   ########.fr       */
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

void	change_number_bg(t_img *img, int size, t_point scale, bool comic)
{
	int	x;
	int	y;
	t_point	offset;
	int	color;
	t_game *game;
	

	game = mem_save(NULL);
	y = -1;
	color = 0;
	offset.x = WIDTH - 42 * 5;
	offset.y = 25;
	if (size == 0)
		offset.x -= 120;
	else if (size == 1)
		offset.x -= 50;
	else if (size == 2)
		offset.x += 20;
	else if (size == 3)
		offset.x += 70;
		
	if(comic == true)
	{
		offset.x -= 80;
		offset.y -= 140;
	}
	while (++y < scale.y)
	{
		x = -1;
		while (++x < scale.x)
		{
			color = pixel_get(img, x, y);
			if ((unsigned int)color != 0xFF000000 && offset.x +  x >= 0 && offset.x + x <= WIDTH && offset.y + y >= 0 && offset.y + y <= HEIGHT)
				my_mlx_pixel_put(&game->bg_img, offset.x + x, y + offset.y, color);
		}
	}
	mlx_destroy_image(game->mlx,img->img);
	free(img);
}

void	create_frame(t_game *game)
{
	static int bob_flag;
	double val;
	t_point scale;
	t_point scale2;
	
	scale.x = 300;
	scale.y = 300;
	scale2.x = 42;
	scale2.y = 100;
	val = 1.0;
	if(game->move[0] || game->move[1] || game->move[2] || game->move[3])
	{
		if(game->player.speed == RUN_SPEED)
			val = 1.5;
		if (bob_flag == 0)
		{
			game->bob += val;
			if(game->bob > 6)
				bob_flag = 1;
		}
		else
		{
			game->bob -= val;
			if(game->bob < -6)
				bob_flag = 0;
		}
	}
	math_with_an_e(game);
	if(game->g_flags.collectibles_exist == true)
	{
		change_number_bg(draw_scaled_img(game, &game->nums[game->collected_comics],scale2, -1), 0, scale2, false);
		change_number_bg(draw_scaled_img(game, &game->slash, scale2, -1), 1, scale2, false);
		change_number_bg(draw_scaled_img(game, &game->nums[game->ass.collect_amount - 1], scale2, -1), 2, scale2, false);
		change_number_bg(draw_scaled_img(game,&game->ass.textures[CL],scale,-1), 3, scale, true);
	}
	mlx_clear_window(game->mlx, game->win);
	if (game->mini.show == true)
		draw_minimap(game, game->player.posx, game->player.posy);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}
