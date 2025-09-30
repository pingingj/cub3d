/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:15:34 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/09/25 14:46:00 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_square(t_game *game, int cx, int cy, int hexa)
{
	if (cx < 0 || cy < 0)
		return ;
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < 60)
	{
		x = 0;
		while (x < 60)
		{
			my_mlx_pixel_put(&game->mini_map, cx + x, cy + y, hexa);
			x++;
		}
		y++;
	}
}

void clear_minimap_image(t_game *game)
{
    for (int y = 0; y < 300; y++)
        for (int x = 0; x < 300; x++)
            my_mlx_pixel_put(&game->mini_map, x, y, 0); // Or your background color
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



void draw_minimap_loop(t_game *game, double playerx, double playery)
{
    clear_minimap_image(game);
    (void)playerx;
    (void)playery;
    
    draw_circle_mlx(game, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, 0xFFFFFF);
}


int	draw_minimap(t_game *game)
{
	draw_minimap_loop(game, game->player.posx, game->player.posy);
	return (0);
}
