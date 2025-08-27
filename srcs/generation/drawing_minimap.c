/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:31:40 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/26 20:06:39 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_wall(t_game *game, int cx, int cy)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < 60)
	{
		x = 0;
		while (x < 60)
		{
			my_mlx_pixel_put(&game->mini_map, cx * 60 + x - 60, cy * 60 + y
				- 60, 0x00FF00);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game, int cx, int cy)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < 60)
	{
		x = 0;
		while (x < 60)
		{
			my_mlx_pixel_put(&game->mini_map, cx * 60 + x - 60, cy * 60 + y
				- 60, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	draw_minimap_loop(t_game *game, double *posx, double *posy, int *y)
{
	int	x;

	while ((*posy) <= game->player.posy + 2)
	{
		x = 1;
		if (game->player.posx - 2 < 0)
			(*posx) = 0;
		else
			(*posx) = game->player.posx - 2;
		while ((*posx) <= game->player.posx + 2 && (*posy) < 13)
		{
			if (game->map[(int)(*posy)][(int)(*posx)] == '0')
				draw_floor(game, x, *y);
			else
				draw_wall(game, x, *y);
			(*posx)++;
			x++;
		}
		(*y)++;
		(*posy)++;
	}
}

int	draw_minimap(t_game *game)
{
	double	posx;
	double	posy;
	int		y;

	posx = 0;
	posy = 0;
	y = 1;
	if (game->player.posy - 2 < 0)
		posy = 0;
	else
		posy = game->player.posy - 2;
	draw_minimap_loop(game, &posx, &posy, &y);
	return (0);
}
