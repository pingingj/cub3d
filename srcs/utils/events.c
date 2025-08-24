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

void move_foward(t_game *game,double speed)
{
    double new_x;
    double new_y;

    new_x = game->player.posx + game->player.dirx * speed;
    new_y = game->player.posy + game->player.diry * speed;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
	mlx_clear_window(game->mlx,game->win);
  //clear_bg_img(game);
	math_with_an_e(game);
  draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
  mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20, 20);
}

void move_back(t_game *game,double speed)
{
    double new_x;
    double new_y;

    new_x = game->player.posx - game->player.dirx * speed;
    new_y = game->player.posy - game->player.diry * speed;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
	mlx_clear_window(game->mlx,game->win);
  //clear_bg_img(game);
	math_with_an_e(game);
  draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
  mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20, 20);
}

void move_left(t_game *game,double speed)
{
    double new_x;
    double new_y;

    new_x = game->player.posx - game->player.planex * speed;
    new_y = game->player.posy - game->player.planey * speed;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
	mlx_clear_window(game->mlx,game->win);
  //clear_bg_img(game);
	math_with_an_e(game);
  draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
  mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20, 20);
}

void move_right(t_game *game,double speed)
{
    double new_x;
    double new_y;

    new_x = game->player.posx + game->player.planex * speed;
    new_y = game->player.posy + game->player.planey * speed;

    if (game->map[(int)new_y][(int)new_x] < '1')
    {
        game->player.posx = new_x;
        game->player.posy = new_y;
    }
	mlx_clear_window(game->mlx,game->win);
  //clear_bg_img(game);
	math_with_an_e(game);
  draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
  mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20, 20);
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
  //clear_bg_img(game);
	math_with_an_e(game);
  draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
  mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20, 20);
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
  //clear_bg_img(game);
	math_with_an_e(game);
  draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
  mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20, 20);
}

int key_press(int keycode,t_game *game)
{
    if (keycode == 65307)
		  closex(game);
    if(keycode == W)
		  game->move[0] = 1;
    if(keycode == S)
      game->move[1] = 1;
    if(keycode == A)
      game->move[2] = 1;
    if(keycode == D)
		  game->move[3] = 1;
    if(keycode == 65363)
		  game->move[4] = 1;
    if(keycode == 65361)
		  game->move[5] = 1;
    if(keycode == SHIFT)
		  game->player.speed = RUN_SPEED;
    return (0);
}

int key_release(int keycode,t_game *game)
{
    if(keycode == W)
		game->move[0] = 0;
    if(keycode == S)
      game->move[1] = 0;
    if(keycode == A)
      game->move[2] = 0;
    if(keycode == D)
		  game->move[3] = 0;
    if(keycode == 65363)
		  game->move[4] = 0;
    if(keycode == 65361)
		  game->move[5] = 0;
    if(keycode == SHIFT)
		  game->player.speed = MOVE_SPEED;
    return (0);
}

int move(t_game *game)
{
   	if(game->move[0] == 1) 
		  move_foward(game,game->player.speed);
    if(game->move[1])
      move_back(game,game->player.speed);
    if(game->move[2])
      move_left(game,game->player.speed);
    if(game->move[3])
		  move_right(game,game->player.speed);
    if(game->move[4])
		  look_right(game);
    if(game->move[5])
		  look_left(game);
    return (0);
}
