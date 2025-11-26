/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:07:03 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/26 19:21:05 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

// bool	hit_box(t_game *game,double x,double y)
// {
// 	int i;
// 	double new_x;
// 	double new_y;
// 	double angle;

// 	i = 0;
// 	while(i < ANGLE_NUMBERS)
// 	{
// 		angle = (2 * PI/ANGLE_NUMBERS) * i;
// 		new_x = x + cos(angle) * RADIUS;
// 		new_y = y + sin(angle) * RADIUS;
// 		if(game->map.grid[(int)new_y][(int)new_x] == '1' || game->map.grid[(int)new_y][(int)new_x] == 'd')
// 			return (false);
// 		i++;
// 	}
// 	return(true);
// }

bool	hit_box(t_game *game, double x, double y, int who)
{
	int		i;
	double	new_x;
	double	new_y;
	double	angle;

	(void)who;
	i = 0;
	while (i < ANGLE_NUMBERS)
	{
		angle = (2 * PI / ANGLE_NUMBERS) * i;
		new_x = x + cos(angle) * RADIUS;
		new_y = y + sin(angle) * RADIUS;
		if (game->map.grid[(int)new_y][(int)new_x] == 'd')
			return (false);
		if (game->map.grid[(int)new_y][(int)new_x] == '1' && who == 1)
			return (false);
		i++;
	}
	return (true);
}

void	move_foward(t_game *game, double speed)
{
	double	new_x;
	double	new_y;
	int		i;

	new_x = game->player.posx + game->player.dirx * speed;
	new_y = game->player.posy + game->player.diry * speed;
	if (hit_box(game, new_x, game->player.posy, 1) == true)
		game->player.posx = new_x;
	if (hit_box(game, game->player.posx, new_y, 1) == true)
		game->player.posy = new_y;
	if (game->map.grid[(int)new_y][(int)new_x] == 'c')
	{
		i = 0;
		while (i < game->ass.collect_amount)
		{
			if ((int)game->ass.sprites[i].cords.x == (int)new_x
				&& (int)game->ass.sprites[i].cords.y == (int)new_y
				&& game->ass.sprites[i].exists == true)
			{
				game->collected_comics++;
				game->ass.sprites[i].exists = false;
			}
			i++;
		}
	}
}

void	move_back(t_game *game, double speed)
{
	double	new_x;
	double	new_y;
	int		i;

	new_x = game->player.posx - game->player.dirx * speed;
	new_y = game->player.posy - game->player.diry * speed;
	if (hit_box(game, new_x, game->player.posy, 1) == true)
		game->player.posx = new_x;
	if (hit_box(game, game->player.posx, new_y, 1) == true)
		game->player.posy = new_y;
	if (game->map.grid[(int)new_y][(int)new_x] == 'c')
	{
		i = 0;
		while (i < game->ass.collect_amount)
		{
			if ((int)game->ass.sprites[i].cords.x == (int)new_x
				&& (int)game->ass.sprites[i].cords.y == (int)new_y
				&& game->ass.sprites[i].exists == true)
			{
				game->collected_comics++;
				game->ass.sprites[i].exists = false;
			}
			i++;
		}
	}
}

void	move_left(t_game *game, double speed)
{
	double	new_x;
	double	new_y;
	int		i;

	new_x = game->player.posx - game->player.planex * speed;
	new_y = game->player.posy - game->player.planey * speed;
	if (hit_box(game, new_x, game->player.posy, 1) == true)
		game->player.posx = new_x;
	if (hit_box(game, game->player.posx, new_y, 1) == true)
		game->player.posy = new_y;
	if (game->map.grid[(int)new_y][(int)new_x] == 'c')
	{
		i = 0;
		while (i < game->ass.collect_amount)
		{
			if ((int)game->ass.sprites[i].cords.x == (int)new_x
				&& (int)game->ass.sprites[i].cords.y == (int)new_y
				&& game->ass.sprites[i].exists == true)
			{
				game->collected_comics++;
				game->ass.sprites[i].exists = false;
			}
			i++;
		}
	}
}

void	move_right(t_game *game, double speed)
{
	double	new_x;
	double	new_y;
	int		i;

	new_x = game->player.posx + game->player.planex * speed;
	new_y = game->player.posy + game->player.planey * speed;
	if (hit_box(game, new_x, game->player.posy, 1) == true)
		game->player.posx = new_x;
	if (hit_box(game, game->player.posx, new_y, 1) == true)
		game->player.posy = new_y;
	if (game->map.grid[(int)new_y][(int)new_x] == 'c')
	{
		i = 0;
		while (i < game->ass.collect_amount)
		{
			if ((int)game->ass.sprites[i].cords.x == (int)new_x
				&& (int)game->ass.sprites[i].cords.y == (int)new_y
				&& game->ass.sprites[i].exists == true)
			{
				game->collected_comics++;
				game->ass.sprites[i].exists = false;
			}
			i++;
		}
	}
}
