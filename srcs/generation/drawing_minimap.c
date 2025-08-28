/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:15:34 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/28 19:31:26 by dgarcez-         ###   ########.fr       */
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
				- 60, 0x000000);
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
				- 60, 0x0000AF);
			x++;
		}
		y++;
	}
}

void draw_filled_circle_mlx(t_game *game, int cx, int cy, int color)
{
    int x;
    int y;

    y = cy - RADIUS;
    while (y <= cy + RADIUS)
    {
        x = cx - RADIUS;
        while (x <= cx + RADIUS)
        {
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= RADIUS * RADIUS)
                my_mlx_pixel_put(&game->mini_map, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_circle_mlx(t_game *game, int cx, int cy, int color)
{
	int i;
	int	x;
	int	y;

	i = 0;
    while (i < ANGLE_NUMBERS)
    {
		double angle = (2 * PI * i) / ANGLE_NUMBERS;
		x = (int)(cx + cos(angle) * 5);
		y = (int)(cy + sin(angle) * 5);
		draw_filled_circle_mlx(game, x, y, color);
		i++;
    }
}


void	draw_minimap_loop(t_game *game)
{
	
	draw_circle_mlx(game, 150, 150, 0xFFFFFF);
}

int	draw_minimap(t_game *game)
{
	draw_minimap_loop(game);
	return (0);
}
