/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/20 14:43:07 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	mouse(int x, int y, t_game *game)
{
	game->mouse.x = x - WIDTH / 2;
	if (x > WIDTH / 2)
		game->move[4] = 1;
	if (x < WIDTH / 2)
		game->move[5] = 1;
	if (x == WIDTH / 2)
	{
		game->move[4] = 0;
		game->move[5] = 0;
	}
	game->mouse.y = y - HEIGHT / 2;
	if (y > HEIGHT / 2)
	{
		game->player.look -= game->mouse.y / 10;
		if (game->player.look < -1000)
			game->player.look += game->mouse.y / 10;
	}
	if (y < HEIGHT / 2)
	{
		game->player.look += -game->mouse.y / 10;
		if (game->player.look > 1000)
			game->player.look -= -game->mouse.y / 10;
	}
	if (x != WIDTH / 2 || y != HEIGHT / 2)
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

void	draw_title(t_game *game, int i)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while(x < WIDTH)
	{
		y = 0;
		while(y < HEIGHT)
		{
			color = pixel_get(&game->title[i], x, y);
			my_mlx_pixel_put(&game->bg_img, x, y, color);
			y++;
		}
		x++;
	}
}

int	menu(t_game *game)
{
	static int		frame = 0;
	static double	last_ms;
	struct timeval	now;
	double			now_ms;
	double	frame_ms;

	gettimeofday(&now, NULL);
	now_ms = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
	if (last_ms == 0.0)
		last_ms = now_ms;
	frame_ms = 0;
	if (frame >= 93)
		frame_ms = 30;
	if (now_ms - last_ms >= frame_ms)
	{
		mlx_clear_window(game->mlx, game->win);
		draw_title(game, frame);
		mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
		frame++;
		last_ms = now_ms;
	}
	if (frame > 193)
		frame = 152;
	return (1);
}


int	main_loop(t_game *game)
{
	menu(game);
	// move(game);
	// if (game->ass.enemy.cords.x != -1)
	// 	monster(game);
	// create_frame(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc == 2)
	{
		if (parse(&game, argv[1]) == false)
			return (1);
		game.mlx = mlx_init();
		print_info(game);
		textures(&game);
		map_gen(&game);
		mlx_hook(game.win, 17, 0, closex, &game);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 6, 1L << 6, mouse, &game);
		mlx_loop_hook(game.mlx, main_loop, &game);
		mlx_loop(game.mlx);
		free_game(&game);
		return (1);
	}
	else
		return (print_errors(&game, 1, "Not valid amount of arguments"), 1);
	return (0);
}
