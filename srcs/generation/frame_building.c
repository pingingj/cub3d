/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_building.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:37 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/05 16:59:05 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	bob_the_builder(t_game *game)
{
	static int	bob_flag;

	if (game->move[forwards] || game->move[backwards] || game->move[left]
		|| game->move[right])
	{
		if ((game->move[left] && game->move[right]))
			game->bob = 0;
		else
		{
			if (bob_flag == 0)
			{
				game->bob += game->player.speed * 12.0;
				if (game->bob > 6)
					bob_flag = 1;
			}
			else
			{
				game->bob -= game->player.speed * 12.0;
				if (game->bob < -6)
					bob_flag = 0;
			}
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
	bob_the_builder(game);
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
	if (game->ass.collect_amount > 0)
		hande_sprites(game);
}

static t_point	change_offset(int size, bool comic)
{
	t_point	offset;

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
	if (comic == true)
	{
		offset.x -= 80;
		offset.y -= 140;
	}
	return (offset);
}

void	change_number_bg(t_img *img, int size, t_point scale, bool comic)
{
	t_point	coords;
	t_point	offset;
	int		color;
	t_game	*game;

	game = mem_save(NULL);
	if (!img)
		print_errors(game, 2, "New Img Failed");
	coords.y = -1;
	offset = change_offset(size, comic);
	while (++coords.y < scale.y)
	{
		coords.x = -1;
		while (++coords.x < scale.x)
		{
			color = pixel_get(img, coords.x, coords.y);
			if ((unsigned int)color != 0xFF000000 && offset.x + coords.x >= 0
				&& offset.x + coords.x <= WIDTH && offset.y + coords.y >= 0
				&& offset.y + coords.y <= HEIGHT)
				my_mlx_pixel_put(&game->bg_img, offset.x + coords.x, coords.y
					+ offset.y, color);
		}
	}
	mlx_destroy_image(game->mlx, img->img);
	free(img);
}

void	create_frame(t_game *game)
{
	t_point	scale;
	t_point	scale2;

	scale.x = 300;
	scale.y = 300;
	scale2.x = 42;
	scale2.y = 100;
	math_with_an_e(game);
	if (game->g_flags.collectibles_exist == true)
	{
		change_number_bg(draw_scaled_img(game,
				&game->nums[game->collected_comics], scale2, -1), 0, scale2,
			false);
		change_number_bg(draw_scaled_img(game, &game->slash, scale2, -1), 1,
			scale2, false);
		change_number_bg(draw_scaled_img(game,
				&game->nums[game->ass.collect_amount - 1], scale2, -1), 2,
			scale2, false);
		change_number_bg(draw_scaled_img(game, &game->ass.textures[CL], scale,
				-1), 3, scale, true);
	}
	mlx_clear_window(game->mlx, game->win);
	if (game->mini.show == true)
		draw_minimap(game, game->player.posx, game->player.posy);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}
