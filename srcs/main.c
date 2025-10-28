/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/28 12:55:33 by dpaes-so         ###   ########.fr       */
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

void ft_sleep(double mili_secs)
{
    double last_time = 0.0;
    struct timeval now;
    double current_time;

    if (mili_secs <= 0.0)
        return;

    gettimeofday(&now, NULL);
    current_time = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
    if (last_time == 0.0)
        last_time = current_time;
    while (1)
    {
        gettimeofday(&now, NULL);
        current_time = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
        if (current_time - last_time >= mili_secs)
            break;
    }
}

double fps_counter(t_game *game)
{
    static int frames;
    struct timeval now;
    static double last_time;
    static double next_deadline_ms;
    double current_time;
    double fsleep = 0.0;

    if (game->fps_lock > 0)
    {
        double target_ms = 1000.0 / (double)game->fps_lock;
        gettimeofday(&now, NULL);
        double now_ms = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
        if (next_deadline_ms == 0.0)
            next_deadline_ms = now_ms + target_ms;
        fsleep = next_deadline_ms - now_ms;
        if (fsleep < 0.0)
            fsleep = 0.0;
        next_deadline_ms += target_ms;
        if (next_deadline_ms < now_ms - target_ms)
            next_deadline_ms = now_ms + target_ms;
    }
    else
        next_deadline_ms = 0.0;
    gettimeofday(&now, NULL);
    current_time = now.tv_sec + now.tv_usec / 1000000.0;
    if (last_time == 0.0)
        last_time = current_time;
    frames++;
    if (current_time - last_time >= 1.0)
    {
        // ft_printf("FPS: %d\n", frames);
        frames = 0;
        last_time = current_time;
    }
    return (fsleep);
}

int main_loop(t_game *game)
{
    double fsleep;

    move(game);
    if (game->ass.enemy.cords.x != -1)
        monster(game);
    create_frame(game);
    fsleep = fps_counter(game);
    if (game->fps_lock > 0 && fsleep > 0.0)
        ft_sleep(fsleep);
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
		game.fps_lock = 60;
		game.mlx = mlx_init();
		print_info(game);
		textures(&game);
		map_gen(&game);
        // printf("dasdasdadsadasdsadas    1\n");
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
