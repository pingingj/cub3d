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
    double new_x = game->player.posx + game->player.dirx * MOVE_SPEED;
    double new_y = game->player.posy + game->player.diry * MOVE_SPEED;

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
    double new_x = game->player.posx - game->player.dirx * MOVE_SPEED;
    double new_y = game->player.posy - game->player.diry * MOVE_SPEED;

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
    double new_x = game->player.posx - game->player.planex * MOVE_SPEED;
    double new_y = game->player.posy - game->player.planey * MOVE_SPEED;

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
    double new_x = game->player.posx + game->player.planex * MOVE_SPEED;
    double new_y = game->player.posy + game->player.planey * MOVE_SPEED;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
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
	return (0);
}