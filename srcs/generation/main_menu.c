/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:58:18 by dpaes-so          #+#    #+#             */
/*   Updated: 2026/06/16 23:44:39 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	spawn_comics(t_game *game)
{
	static int	i;
	static int	wave;
	int			amount;
	int			checked = 0;
	int			spawned = 0;
	
	if (wave % 2 == 0)
		amount = 4;
	else
		amount = 3;
	wave++;
	while(spawned < amount && checked < 20)
	{
		if (i >= 20)
			i = 0;
		if (game->comics[i].active == false)
		{
			game->comics[i].active = true;
			if (i % 2 == 0)
				game->comics[i].type = 'B';
			else
				game->comics[i].type = 'D';	
			game->comics[i].frame = 0;
			game->comics[i].coords.x = rand() % (WIDTH - 300);
			game->comics[i].coords.y = -300;
			spawned++;
		}
		checked++;
		i++;
	}
}

void	draw_books(t_game *game)
{
	int	i;
	int	x;
	int	y;
	unsigned int	color;
	t_img	cur_img;

	i = 0;
	while (i < 20)
	{
		if (game->comics[i].active == false)
		{
			i++;
			continue;
		}
		if (game->comics[i].type == 'B')
			cur_img = game->animated_comic;
		else
			cur_img = game->animated_dark;
		x = 0;
		while (x < 300)
		{
			y = 0;
			while (y < 300)
			{
				color = pixel_get(&cur_img, game->comics[i].frame * 300 + x, y);
				// printf("%x\n", color);
				if (game->comics[i].coords.y + y > 0 && game->comics[i].coords.y + y < HEIGHT && color != 0xff000000)
					my_mlx_pixel_put(&game->title, game->comics[i].coords.x + x, game->comics[i].coords.y + y, color);
				y++;
			}
			x++;
		}
		game->comics[i].frame++;
		if (game->comics[i].frame >= 30)
			game->comics[i].frame = 0;
   		game->comics[i].coords.y += 10;
		if (game->comics[i].coords.y >= HEIGHT)
			game->comics[i].active = false;
		i++;
	}
}

void	draw_title(t_game *game)
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
			if ((x / (WIDTH / 6)) % 2 == 0)
				color = 0x682B80;
			else
				color = 0x49165D; 
			my_mlx_pixel_put(&game->title, x, y, color);
			y++;
		}
		x++;
	}
	draw_books(game);
}

void	menu_scale(t_game *game, double now_ms, double *last_ms)
{
	t_img	*scaled;
	t_point	scale;

	draw_title(game);
	scale.x = WIDTH;
	scale.y = HEIGHT;
	scaled = draw_scaled_img(game, &game->title, scale, -1);
	if (scaled == NULL)
		print_errors(game, 2, "New img failed in menu_scale");
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, scaled->img, 0, 0);
	mlx_destroy_image(game->mlx, scaled->img);
	free(scaled);
	(*last_ms) = now_ms;
}

int	menu(t_game *game)
{
	static int		frame;
	static double	last_ms;
	struct timeval	now;
	double			now_ms;
	double			frame_ms;

	game->g_flags.button_ready = true;
	gettimeofday(&now, NULL);
	now_ms = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
	if (last_ms == 0.0)
		last_ms = now_ms;
	frame_ms = 50;
	if (now_ms - last_ms >= frame_ms)
	{
		if (frame % 40 == 0)
			spawn_comics(game);
		menu_scale(game, now_ms, &last_ms);
		frame++;
		if (frame > 200)
			frame = 0;
	}
	return (1);
}
