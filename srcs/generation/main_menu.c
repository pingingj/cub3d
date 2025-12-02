/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:58:18 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 18:12:05 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_title(t_game *game, int i)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			color = pixel_get(&game->title[i], x, y);
			my_mlx_pixel_put(&game->bg_img, x, y, color);
			y++;
		}
		x++;
	}
}

void	menu_scale(int *frame, t_game *game, double now_ms, double last_ms)
{
	t_img	*scaled;
	t_point	scale;

	scale.x = WIDTH;
	scale.y = HEIGHT;
	scaled = draw_scaled_img(game, &game->title[(*frame)], scale, -1);
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, scaled->img, 0, 0);
	mlx_destroy_image(game->mlx, scaled->img);
	free(scaled);
	(*frame)++;
	last_ms = now_ms;
}

int	menu(t_game *game)
{
	static int		frame;
	static double	last_ms;
	struct timeval	now;
	double			now_ms;
	double			frame_ms;

	gettimeofday(&now, NULL);
	now_ms = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
	if (last_ms == 0.0)
		last_ms = now_ms;
	frame_ms = 0;
	if (frame >= 93)
	{
		frame_ms = 30;
		game->g_flags.button_ready = true;
	}
	if (now_ms - last_ms >= frame_ms)
		menu_scale(&frame, game, now_ms, last_ms);
	if (frame > 193)
		frame = 152;
	return (1);
}
