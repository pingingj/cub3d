/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:07:03 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/19 15:09:15 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void move_foward(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->player.posx + game->player.dirx * MOVE_SPEED;
    new_y = game->player.posy + game->player.diry * MOVE_SPEED;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
	mlx_clear_window(game->mlx,game->win);
	math_with_an_e(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}

void move_back(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->player.posx - game->player.dirx * MOVE_SPEED;
    new_y = game->player.posy - game->player.diry * MOVE_SPEED;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
	mlx_clear_window(game->mlx,game->win);
	math_with_an_e(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}

void move_left(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->player.posx - game->player.planex * MOVE_SPEED;
    new_y = game->player.posy - game->player.planey * MOVE_SPEED;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
	mlx_clear_window(game->mlx,game->win);
	math_with_an_e(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}

void move_right(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->player.posx + game->player.planex * MOVE_SPEED;
    new_y = game->player.posy + game->player.planey * MOVE_SPEED;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
	mlx_clear_window(game->mlx,game->win);
	math_with_an_e(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}

/*to lookj in both direction i use a formula that rotates vectors, since for the camere i have the direction and the plane (fov)
    i need to rotate both, but thats just it*/
void look_right(t_game *game)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = game->player.dirx;
    game->player.dirx = game->player.dirx * cos(rot_speed) - game->player.diry * sin(rot_speed);
    game->player.diry = oldDirX * sin(rot_speed) + game->player.diry * cos(rot_speed);

    oldPlaneX = game->player.planex;
    game->player.planex =  game->player.planex * cos(rot_speed) -  game->player.planey * sin(rot_speed);
    game->player.planey = oldPlaneX * sin(rot_speed) +  game->player.planey * cos(rot_speed);
	mlx_clear_window(game->mlx,game->win);
	math_with_an_e(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}
void look_left(t_game *game)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = game->player.dirx;
    game->player.dirx = game->player.dirx * cos(-rot_speed) - game->player.diry * sin(-rot_speed);
    game->player.diry = oldDirX * sin(-rot_speed) + game->player.diry * cos(-rot_speed);

    oldPlaneX = game->player.planex;
    game->player.planex =  game->player.planex * cos(-rot_speed) -  game->player.planey * sin(-rot_speed);
    game->player.planey = oldPlaneX * sin(-rot_speed) +  game->player.planey * cos(-rot_speed);
	mlx_clear_window(game->mlx,game->win);
	math_with_an_e(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}

int	keys(int keycode, t_game *mlx)
{
	if (keycode == 65307)
		closex(mlx);
	if(keycode == W)
		move_foward(mlx);
	if(keycode == S)
		move_back(mlx);
	if(keycode == A)
		move_left(mlx);
	if(keycode == D)
		move_right(mlx);
    if(keycode == 65363)
		look_right(mlx);
    if(keycode == 65361)
		look_left(mlx);
	return (0);
}