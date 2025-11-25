/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:29:06 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/25 15:47:06 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	way_too_many_press_keys(int keycode, t_game *game)
{
	if (keycode == ARROW_RIGHT)
	{
		game->g_flags.look_flag_right = true;
		game->move[arrow_right] = 1;
	}
	if (keycode == ARROW_LEFT)
	{
		game->g_flags.look_flag_left = true;
		game->move[arrow_left] = 1;
	}
	if (keycode == ARROW_UP)
		game->move[arrow_up] = 1;
	if (keycode == ARROW_DOWN)
		game->move[arrow_down] = 1;
	if (keycode == F)
		open_door(game, game->player.posx + game->player.dirx * MOVE_SPEED,
			game->player.posy + game->player.diry * MOVE_SPEED);
	if (keycode == 44)
		game->move[zoom_in] = 1;
	if (keycode == 46)
		game->move[zoom_out] = 1;
	if (keycode == ENTER && game->g_flags.button_ready == true
		&& game->g_flags.game_state == main_menu)
		game->g_flags.game_state = running;
}

void	too_many_press_keys(int keycode, t_game *game)
{
	if (keycode == L)
		game->g_flags.laggy_lantern = !game->g_flags.laggy_lantern;
	if (keycode == H)
		change_flag(H, game);
	if (keycode == P)
		change_flag(P, game);
	if (keycode == SHIFT)
		game->player.speed = RUN_SPEED;
	way_too_many_press_keys(keycode, game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		closex(game);
	if (keycode == M)
	{
		if (game->mini.show == false)
			game->mini.show = true;
		else
			game->mini.show = false;
	}
	if (keycode == W)
		game->move[forwards] = 1;
	if (keycode == S)
		game->move[backwards] = 1;
	if (keycode == A)
		game->move[left] = 1;
	if (keycode == D)
		game->move[right] = 1;
	too_many_press_keys(keycode, game);
	return (0);
}

void	too_many_release_keys(int keycode, t_game *game)
{
	if (keycode == ARROW_UP)
		game->move[arrow_up] = 0;
	if (keycode == ARROW_DOWN)
		game->move[arrow_down] = 0;
	if (keycode == SHIFT)
		game->player.speed = MOVE_SPEED;
	if (keycode == 44)
		game->move[zoom_in] = 0;
	if (keycode == 46)
		game->move[zoom_out] = 0;
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->move[forwards] = 0;
	if (keycode == S)
		game->move[backwards] = 0;
	if (keycode == A)
		game->move[left] = 0;
	if (keycode == D)
		game->move[right] = 0;
	if (keycode == ARROW_RIGHT)
	{
		game->g_flags.look_flag_right = false;
		game->move[arrow_right] = 0;
	}
	if (keycode == ARROW_LEFT)
	{
		game->g_flags.look_flag_left = false;
		game->move[arrow_left] = 0;
	}
	too_many_release_keys(keycode, game);
	return (0);
}
