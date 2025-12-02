/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:03:57 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 18:07:07 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	mouse2(int x, int y, t_game *game)
{
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
}

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
	mouse2(x, y, game);
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
