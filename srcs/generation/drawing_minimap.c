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
			// printf("%d + %d = %d %d + %d = %d\n", cx, x, cx + x, cy, y, cy + y);
			my_mlx_pixel_put(&game->mini_map, cx + x, cy + y, hexa);
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
void clear_minimap_image(t_game *game)
{
    for (int y = 0; y < 300; y++)
        for (int x = 0; x < 300; x++)
            my_mlx_pixel_put(&game->mini_map, x, y, 0x000000); // Or your background color
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


void	draw_minimap_loop(t_game *game, double playerx, double playery)
{
	clear_minimap_image(game);
	int	ind_x;
	int	ind_y;
	int	m_mapx;
	int	m_mapy;
	double	draw_x;
	double	draw_y;
	double	fract_x;
	double	fract_y;

	// printf("helo\n");
	ind_y = -2;
	while(ind_y <= 2)
	{
		ind_x = -2;
		while(ind_x <= 2)
		{
			m_mapx = ind_x + (int)playerx;
			m_mapy = ind_y + (int)playery;
			fract_x = playerx - (int)playerx;
			fract_y = playery - (int)playery;
			draw_x = (ind_x + 2 - fract_x) * 60;
			draw_y = (ind_y + 2 - fract_y) * 60;

			printf("playerx = %f playery = %f mapx = %d map y = %d draw x = %f draw_y = %f\n", playerx, playery, m_mapx, m_mapy, draw_x, draw_y);
			if (m_mapx >= 0 && m_mapy >= 0 && m_mapx < ft_strlen(game->map.grid[(int)m_mapy])
				&& m_mapy < game->map.pos.y)
			{
				if (game->map.grid[m_mapy][m_mapx] == '1')
					draw_square(game, (int)draw_x, (int)draw_y, 0x0000AF);
				else if (game->map.grid[m_mapy][m_mapx] == 'o')
					draw_square(game, (int)draw_x, (int)draw_y, 6691327);
				else
					draw_square(game, (int)draw_x, (int)draw_y, 0xFFFFFF);
			}
			else
				draw_square(game, (int)draw_x, (int)draw_y, 0xFFFFFF);
			ind_x++;
		}
		ind_y++;
	}
	draw_circle_mlx(game, 150, 150, 0xFFFFFF);
}

int	draw_minimap(t_game *game)
{
	draw_minimap_loop(game, game->player.posx, game->player.posy);
	return (0);
}
