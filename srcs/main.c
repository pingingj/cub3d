/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/02 13:30:06 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	mouse(int x, int y, t_game *game)
{
	game->mouse.x = x - WIDTH / 2;
	if (game->g_flags.game_state != running)
		return (1);
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
	if (game->g_flags.game_state == running)
	{
		if (x != WIDTH / 2 || y != HEIGHT / 2)
			mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

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

int	menu(t_game *game)
{
	static int		frame = 0;
	static double	last_ms;
	struct timeval	now;
	double			now_ms;
	double			frame_ms;
	t_point			scale;
	t_img			*scaled;

	scale.x = WIDTH;
	scale.y = HEIGHT;
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
	{
		scaled = draw_scaled_img(game, &game->title[frame], scale, -1);
		mlx_clear_window(game->mlx, game->win);
		mlx_put_image_to_window(game->mlx, game->win, scaled->img, 0, 0);
		mlx_destroy_image(game->mlx, scaled->img);
		free(scaled);
		frame++;
		last_ms = now_ms;
	}
	if (frame > 193)
		frame = 152;
	return (1);
}

int	main_loop(t_game *game)
{
	double	fsleep;

	if (game->g_flags.game_state == main_menu)
		menu(game);
	else if (game->g_flags.game_state == death_screen)
		make_fade_screen(game, &game->ass.death_screen);
	else if (game->g_flags.game_state == Pause)
		make_pause_screen(game);
	else if (game->g_flags.game_state == Win_screen)
		make_fade_screen(game, &game->ass.win_screen);
	else
	{
		if (game->collected_comics == game->ass.collect_amount - 1
			&& game->g_flags.game_state != Finished
			&& game->g_flags.collectibles_exist == true)
			game->g_flags.game_state = Win_screen;
		if (game->g_flags.game_state == running)
		{
			action(game);
			if (game->ass.enemy.cords.x != -1)
				monster(game);
			create_frame(game);
			fsleep = fps_counter(game);
			if (game->fps_lock > 0 && fsleep > 0.0)
				ft_sleep(fsleep);
			door_timer(game);
		}
	}
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_game *game)
{
	if (keycode == 1 && game->g_flags.button_ready == true
		&& game->g_flags.game_state == main_menu)
	{
		if (x >= WIDTH / 3 && x <= WIDTH / 1.523809524 && y >= HEIGHT
			/ 2.097087379 && y <= HEIGHT / 1.588235294)
			game->g_flags.game_state = running;
		if (x >= WIDTH / 3 && x <= WIDTH / 1.523809524 && y >= HEIGHT
			/ 1.421052632 && y <= HEIGHT / 1.161290323)
			closex(game);
	}
	return (1);
}

t_game	*mem_save(t_game *to_save)
{
	static t_game	*save;

	if (to_save)
		save = to_save;
	return (save);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc == 2)
	{
		if (parse(&game, argv[1]) == false)
			return (1);
		game.fps_lock = 60;
		game.g_flags.game_state = running;
		game.mlx = mlx_init();
		mem_save(&game);
		// print_info(game);
		textures(&game);
		map_gen(&game);
		mlx_hook(game.win, 17, 0, closex, &game);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 6, 1L << 6, mouse, &game);
		mlx_hook(game.win, 04, 1L << 2, mouse_press, &game);
		mlx_loop_hook(game.mlx, main_loop, &game);
		mlx_loop(game.mlx);
		free_game(&game);
		return (1);
	}
	else
		return (print_errors(&game, 1, "Not valid amount of arguments"), 1);
	return (0);
}
