/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:22:52 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/09 16:56:26 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static bool	open_door(t_game *game, double x, double y)
{
	int		i;
	double	new_x;
	double	new_y;
	double	angle;

	i = 0;
	while (i < ANGLE_NUMBERS)
	{
		angle = (2 * PI / ANGLE_NUMBERS) * i;
		new_x = x + cos(angle) * 0.4;
		new_y = y + sin(angle) * 0.4;
		if (game->map.grid[(int)new_y][(int)new_x] == 'd'
			&& game->meth.looking_door == true)
		{
			game->map.grid[(int)new_y][(int)new_x] = 'D';
			create_frame(game);
			return (true);
		}
		if (game->map.grid[(int)new_y][(int)new_x] == 'D'
			&& game->meth.looking_door == true)
		{
			game->map.grid[(int)new_y][(int)new_x] = 'd';
			if (hit_box(game, x, y) == false)
			{
				game->map.grid[(int)new_y][(int)new_x] = 'D';
				return (false);
			}
			create_frame(game);
			return (true);
		}
		i++;
	}
	return (false);
}

void	look_left(t_game *game)
{
	double	old_dirx;
	double	old_planex;
	double angle;
	int x;

	x= -1;
	angle = ARROW_ROT_SPEED;
	if(game->look_flag_left == false)
	{
		x = game->mouse.x;
		angle = ROT_SPEED;
	}
	old_dirx = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(x * angle) - game->player.diry
		* sin(x * angle);
	game->player.diry = old_dirx * sin(x * angle) + game->player.diry
		* cos(x * angle);
	old_planex = game->player.planex;
	game->player.planex = game->player.planex * cos(x * angle)
		- game->player.planey * sin(x * angle);
	game->player.planey = old_planex * sin(x * angle) + game->player.planey
		* cos(x * angle);
}

int	key_press(int keycode, t_game *game)
{
	// printf("key code = %d\n", keycode);
	if (keycode == 65307)
		closex(game);
	if (keycode == M)
	{
		if (game->mini.show == false)
		{
			game->mini.show = true;
			create_frame(game);
		}
		else
		{
			game->mini.show = false;
			create_frame(game);
		}
	}
	if (keycode == W)
		game->move[0] = 1;
	if (keycode == S)
		game->move[1] = 1;
	if (keycode == A)
		game->move[2] = 1;
	if (keycode == D)
		game->move[3] = 1;
	if (keycode == ARROW_RIGHT)
	{
		game->look_flag_right = true;
		game->move[4] = 1;
	}
	if (keycode == ARROW_LEFT)
	{
		game->look_flag_left = true;
		game->move[5] = 1;
	}
	if (keycode == ARROW_UP)
		game->move[6] = 1;
	if (keycode == ARROW_DOWN)
		game->move[7] = 1;
	if (keycode == SHIFT)
		game->player.speed = RUN_SPEED;
	if (keycode == F)
		open_door(game, game->player.posx + game->player.dirx * MOVE_SPEED,
			game->player.posy + game->player.diry * MOVE_SPEED);
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
	{
		game->look_flag_right = false;
		game->move[4] = 0;
	}
	if (keycode == ARROW_LEFT)
	{
		game->look_flag_left = false;
		game->move[5] = 0;
	}
	if (keycode == ARROW_UP)
		game->move[6] = 0;
	if (keycode == ARROW_DOWN)
		game->move[7] = 0;
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
	if (game->move[6] == 1)
	{
		game->player.look += 10;
		if(game->player.look > 1000)
		game->player.look -=10;
	}
	if (game->move[7] == 1)
	{
		game->player.look -= 10;
		if(game->player.look < -1000)
		game->player.look +=10;
	}
	if (game->move[0] == 1 || game->move[1] == 1 || game->move[2] == 1
		|| game->move[3] == 1 || game->move[4] == 1 || game->move[5] == 1
		|| game->move[6] == 1 || game->move[7] == 1)

	{

		create_frame(game);
	}
	return (0);
}
