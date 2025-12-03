/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/03 18:29:46 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	running_loops(t_game *game)
{
	double	fsleep;

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

int	main_loop(t_game *game)
{
	static int	autoclose;

	if (game->g_flags.game_state == main_menu)
		menu(game);
	else if (game->g_flags.game_state == death_screen)
		make_fade_screen(game, &game->ass.death_screen);
	else if (game->g_flags.game_state == Pause)
		make_pause_screen(game);
	else if (game->g_flags.game_state == Win_screen)
		make_fade_screen(game, &game->ass.win_screen);
	else
		running_loops(game);
	if (game->g_flags.game_state == Finished)
	{
		if (autoclose < 20)
			ft_sleep(100);
		else
			closex(game);
		autoclose++;
	}
	return (0);
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
		game.mlx = mlx_init();
		game.g_flags.game_state = running;
		mem_save(&game);
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
