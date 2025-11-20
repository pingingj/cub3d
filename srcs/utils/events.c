/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finn <finn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:22:52 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/20 00:05:55 by finn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void extra_action(t_game *game)
{
	if (game->move[6] == 1)
	{
		game->player.look += 10;
		if (game->player.look > 1000)
			game->player.look -= 10;
	}
	if (game->move[7] == 1)
	{
		game->player.look -= 10;
		if (game->player.look < -1000)
			game->player.look += 10;
	}
	if (game->move[8] == 1)
	{
		if (game->mini.tile_size < 80)
			game->mini.tile_size++;
	}
	if (game->move[9] == 1)
	{
		if (game->mini.tile_size > 10)
			game->mini.tile_size--;
	}
}

int	action(t_game *game)
{
	if (game->move[0] == 1)
		move_foward(game, game->player.speed);
	else if (game->move[1] == 1)
		move_back(game, game->player.speed);
	if (game->move[2] == 1)
		move_left(game, game->player.speed);
	if (game->move[3] == 1)
		move_right(game, game->player.speed);
	if (game->move[4] == 1)
		look_right(game);
	if (game->move[5] == 1)
		look_left(game);
	extra_action(game);
	return (0);
}

static void pause_handle(t_game *game,bool mouse)
{
	if (game->g_flags.game_state == running)
	{
		game->g_flags.game_state = Pause;
		mlx_mouse_show(game->mlx, game->win);
	}
	else if (game->g_flags.game_state == Pause)
	{
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
		if (mouse == true)
			mlx_mouse_hide(game->mlx, game->win);
		game->g_flags.game_state = running;
	}
}
void	change_flag(int key, t_game *game)
{
	static bool	mouse;

	if (key == H)
	{
		if (mouse == false)
		{
			mlx_mouse_hide(game->mlx, game->win);
			mouse = true;
		}
		else
		{
			mlx_mouse_show(game->mlx, game->win);
			mouse = false;
		}
	}
	if (key == P)
		pause_handle(game,mouse);
}
