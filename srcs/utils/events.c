/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:07:03 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/28 11:54:37 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"


bool	hit_box(t_game *game,double x,double y)
{
	int i;
	double new_x;
	double new_y;
	double angle;

	i = 0;
	while(i < ANGLE_NUMBERS)
	{
		angle = (2 * PI/ANGLE_NUMBERS) * i;
		new_x = x + cos(angle) * RADIUS;
		new_y = y + sin(angle) * RADIUS;
		if(game->map.grid[(int)new_y][(int)new_x] == '1')
			return (false);
		i++;
	}
	return(true);
}
void	move_foward(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx + game->player.dirx * speed;
	new_y = game->player.posy + game->player.diry * speed;

	if(hit_box(game,new_x,game->player.posy) == true)
		game->player.posx = new_x;
	if(hit_box(game,game->player.posx,new_y) == true)
		game->player.posy = new_y;
		
	// if (game->map.grid[(int)new_y][(int)new_x] == 'o')
	// {
	// 	game->player.posx = new_x;
	// 	game->player.posy = new_y;
	// }
}

void	move_back(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx - game->player.dirx * speed;
	new_y = game->player.posy - game->player.diry * speed;
	if(hit_box(game,new_x,game->player.posy) == true)
		game->player.posx = new_x;
	if(hit_box(game,game->player.posx,new_y) == true)
		game->player.posy = new_y;
}

void	move_left(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx - game->player.planex * speed;
	new_y = game->player.posy - game->player.planey * speed;
	if(hit_box(game,new_x,game->player.posy) == true)
		game->player.posx = new_x;
	if(hit_box(game,game->player.posx,new_y) == true)
		game->player.posy = new_y;
}

void	move_right(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx + game->player.planex * speed;
	new_y = game->player.posy + game->player.planey * speed;
	if(hit_box(game,new_x,game->player.posy) == true)
		game->player.posx = new_x;
	if(hit_box(game,game->player.posx,new_y) == true)
		game->player.posy = new_y;
}

/*to lookj in both direction i use a formula that rotates vectors,
	since for the camere i have the direction and the plane (fov)
	i need to rotate both, but thats just it*/
void	look_right(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(rot_speed) - game->player.diry
		* sin(rot_speed);
	game->player.diry = old_dirx * sin(rot_speed) + game->player.diry
		* cos(rot_speed);
	old_planex = game->player.planex;
	game->player.planex = game->player.planex * cos(rot_speed)
		- game->player.planey * sin(rot_speed);
	game->player.planey = old_planex * sin(rot_speed) + game->player.planey
		* cos(rot_speed);
}
