/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:22:52 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/28 11:28:07 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	look_left(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(-rot_speed) - game->player.diry
		* sin(-rot_speed);
	game->player.diry = old_dirx * sin(-rot_speed) + game->player.diry
		* cos(-rot_speed);
	old_planex = game->player.planex;
	game->player.planex = game->player.planex * cos(-rot_speed)
		- game->player.planey * sin(-rot_speed);
	game->player.planey = old_planex * sin(-rot_speed) + game->player.planey
		* cos(-rot_speed);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		closex(game);
	if (keycode == W)
		game->move[0] = 1;
	if (keycode == S)
		game->move[1] = 1;
	if (keycode == A)
		game->move[2] = 1;
	if (keycode == D)
		game->move[3] = 1;
	if (keycode == 65363)
		game->move[4] = 1;
	if (keycode == 65361)
		game->move[5] = 1;
	if (keycode == SHIFT)
		game->player.speed = RUN_SPEED;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->move[0] = 0;
	if (keycode == S)
		game->move[1] = 0;
	if (keycode == A)
		game->move[2] = 0;
	if (keycode == D)
		game->move[3] = 0;
	if (keycode == ARROW_RIGHT)
		game->move[4] = 0;
	if (keycode == ARROW_LEFT)
		game->move[5] = 0;
	if (keycode == SHIFT)
		game->player.speed = MOVE_SPEED;
	return (0);
}

int	move(t_game *game)
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
	if (game->move[0] == 1 || game->move[1] == 1 || game->move[2] == 1
		|| game->move[3] == 1 || game->move[4] == 1 || game->move[5] == 1)
	{
		math_with_an_e(game);
		// draw_minimap(game);
		mlx_clear_window(game->mlx, game->win);
		mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
		// mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20,
			// 20);
	}
	return (0);
}
