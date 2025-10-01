/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:15:34 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/09/30 17:02:27 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void clear_minimap_image(t_game *game, t_pos area)
{
	int y;
	int x;
	
	y = 0;
    while (y < area.y)
	{
		x = 0;
        while (x < area.x)
		{
            my_mlx_pixel_put(&game->bg_img, x + game->mini.offset, y + game->mini.offset, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void draw_filled_circle_mlx(t_game *game, int cx, int cy, int color)
{
    int x;
    int y;

    y = cy - RADIUS_MINI;
    while (y <= cy + RADIUS_MINI)
    {
        x = cx - RADIUS_MINI;
        while (x <= cx + RADIUS_MINI)
        {
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= RADIUS_MINI * RADIUS_MINI)
                my_mlx_pixel_put(&game->bg_img, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_circle_mlx(t_game *game, t_pos center, int color)
{
	int i;
	int	x;
	int	y;

	i = 0;
    while (i < ANGLE_NUMBERS_MINI)
    {
		double angle = (2 * PI * i) / ANGLE_NUMBERS_MINI;
		x = (int)(center.x + cos(angle) * 5);
		y = (int)(center.y + sin(angle) * 5);
		draw_filled_circle_mlx(game, x, y, color);
		i++;
    }
}

void	mini_init(t_game *game)
{
	game->mini.height = (int)game->map.pos.y;
	game->mini.width = (int)game->map.pos.x;
	game->mini.offset = 30;
	game->mini.size.x = WIDTH * 0.25;
	game->mini.size.y = HEIGHT * 0.25;
	game->mini.center.x = game->mini.size.x / 2 + game->mini.offset;
	game->mini.center.y = game->mini.size.y / 2 + game->mini.offset;
}

void	draw_square(t_img *bg, int color, t_pos area, t_pos win)
{
	int	x;
	int	y;

	y = -1;
	while (++y < area.y)
	{
		x = -1;
		while (++x < area.x)
			my_mlx_pixel_put(bg, win.x + x, win.y + y, color);
	}
}

void	draw_minimap_row(t_game game, t_pos map_cord, t_pos  win_cord,
		t_pos area)
{
	while (map_cord.x < game.mini.width && win_cord.x <= game.mini.offset + game.mini.size.x)
	{
		area.x = 60;
		if (map_cord.x >= 0)
		{
			if (win_cord.x < game.mini.offset)
			{
				area.x -= game.mini.offset - win_cord.x;
				win_cord.x = game.mini.offset;
			}
			if (win_cord.x + area.x > game.mini.offset + game.mini.size.x)
				area.x -= (win_cord.x + area.x) - (game.mini.offset + game.mini.size.x);
			if (game.map.grid[(int)map_cord.y][(int)map_cord.x] == '1')
				draw_square(&game.bg_img, 0x9DD1E0, area, win_cord);
			if (game.map.grid[(int)map_cord.y][(int)map_cord.x] == 'o')
				draw_square(&game.bg_img, 0x223030, area, win_cord);
			if (game.map.grid[(int)map_cord.y][(int)map_cord.x] == 'd')
				draw_square(&game.bg_img, 0xFFBB23, area, win_cord);
			if (game.map.grid[(int)map_cord.y][(int)map_cord.x] == 'D')
				draw_square(&game.bg_img, 0x8599BA, area, win_cord);
		}
		map_cord.x++;
		win_cord.x += area.x;
	}
}

void	draw_minimap_tiles(t_game game, t_pos map_cord, t_pos win_cord)
{
	t_pos	area;

	while (map_cord.y < game.mini.height && win_cord.y <= game.mini.offset + game.mini.size.y)
	{
		printf("map cord y = %f\n", map_cord.y);
		area.y = 60;
		if (map_cord.y >= 0)
		{
			if (win_cord.y < game.mini.offset)
			{
				area.y -= game.mini.offset - win_cord.y;
				win_cord.y = game.mini.offset;
			}
			if (win_cord.y + area.y > game.mini.offset + game.mini.size.y)
				area.y -= (win_cord.y + area.y) - (game.mini.offset + game.mini.size.y);
			draw_minimap_row(game, map_cord, win_cord, area);
		}
		map_cord.y++;
		win_cord.y += area.y;
	}
}

void draw_miniframe(t_game *game)
{
	int x;
	int	y;

	y = game->mini.offset;
	while(y < game->mini.size.y + game->mini.offset)
	{
		x = game->mini.offset;
		while(x < game->mini.size.x + game->mini.offset)
		{
			if (x < game->mini.offset + 10 || x > game->mini.size.x + 20)
				my_mlx_pixel_put(&game->bg_img, x, y, 0xBB0000);
			if (y < game->mini.offset + 10 || y > game->mini.size.y + 20)
				my_mlx_pixel_put(&game->bg_img, x, y, 0xBB0000);
			x++;	
		}
		y++;
	}
}

void draw_minimap_loop(t_game *game, double playerx, double playery)
{
	mini_init(game);
    clear_minimap_image(game, game->mini.size);
	draw_minimap_tiles(*game, (t_pos){playerx - 4,playery - 3}, (t_pos){game->mini.center.x - 60 * (playerx - floor(playerx) + 4), game->mini.center.y - 60 * (playery - floor(playery) + 3 )});
	draw_miniframe(game);
    draw_circle_mlx(game, game->mini.center, 0xFF0000);
}


int	draw_minimap(t_game *game)
{
	draw_minimap_loop(game, game->player.posx, game->player.posy);
	return (0);
}
