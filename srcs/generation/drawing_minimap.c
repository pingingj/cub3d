/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:15:34 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/06 18:33:22 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	clear_minimap_image(t_game *game, t_pos area)
{
	int	y;
	int	x;

	y = 0;
	while (y < area.y)
	{
		x = 0;
		while (x < area.x)
		{
			my_mlx_pixel_put(&game->bg_img, x + game->mini.offset, y
					+ game->mini.offset, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	draw_filled_circle_mlx(t_game *game, int cx, int cy, int color)
{
	int radius;
	int	x;
	int	y;

	radius = game->mini.tile_size / 6;
	y = cy - radius;
	while (y <= cy + radius)
	{
		x = cx - radius;
		while (x <= cx + radius)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius
				* radius)
				my_mlx_pixel_put(&game->bg_img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_circle_mlx(t_game *game, t_pos center, int color)
{
		draw_filled_circle_mlx(game, (int)center.x, (int)center.y, color);
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

void	draw_tile(t_img *bg, int color, t_pos area, t_pos win)
{
	int	x;
	int	y;

	y = 0;
	while (y < area.y)
	{
		x = 0;
		while (x < area.x)
		{
			my_mlx_pixel_put(bg, win.x + x, win.y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_minitile_row(t_game game, t_pos tile_pos, t_pos win_cord,
		t_pos area)
{
	char	grid;

	while (tile_pos.x < game.mini.width && win_cord.x <= game.mini.offset
		+ game.mini.size.x)
	{
		area.x = game.mini.tile_size;
		if (tile_pos.x >= 0)
		{
			if (win_cord.x < game.mini.offset)
			{
				area.x -= game.mini.offset - win_cord.x;
				win_cord.x = game.mini.offset;
			}
			if (win_cord.x + area.x > game.mini.offset + game.mini.size.x)
				area.x -= (win_cord.x + area.x) - (game.mini.offset
						+ game.mini.size.x);
			grid = game.map.grid[(int)tile_pos.y][(int)tile_pos.x];
			if (grid == '1')
				draw_tile(&game.bg_img, 0x9DD1E0, area, win_cord);
			else if (grid == 'o')
				draw_tile(&game.bg_img, 0x223030, area, win_cord);
			else if (grid == 'd')
				draw_tile(&game.bg_img, 0xFFBB23, area, win_cord);
			else if (grid == 'D')
				draw_tile(&game.bg_img, 0x8599BA, area, win_cord);
		}
		tile_pos.x++;
		win_cord.x += area.x;
	}
}

void	minimap_tiles(t_game game, t_pos tile_pos, t_pos win_pos)
{
	t_pos	area;

	while (tile_pos.y < game.mini.height && win_pos.y <= game.mini.offset
		+ game.mini.size.y)
	{
		area.y = game.mini.tile_size;
		if (tile_pos.y >= 0)
		{
			if (win_pos.y < game.mini.offset)
			{
				area.y -= game.mini.offset - win_pos.y;
				win_pos.y = game.mini.offset;
			}
			if (win_pos.y + area.y > game.mini.offset + game.mini.size.y)
				area.y -= (win_pos.y + area.y) - (game.mini.offset
						+ game.mini.size.y);
			draw_minitile_row(game, tile_pos, win_pos, area);
		}
		tile_pos.y++;
		win_pos.y += area.y;
	}
}

void	draw_miniframe(t_game *game)
{
	int	x;
	int	y;

	y = game->mini.offset;
	while (y < game->mini.size.y + game->mini.offset)
	{
		x = game->mini.offset;
		while (x < game->mini.size.x + game->mini.offset)
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

void	draw_minimap_loop(t_game *game, double playerx, double playery)
{
	t_pos	scale_tiles;
	t_pos	tile_pos;
	t_pos	win_pos;
	
	printf("tilesize = %d\n", game->mini.tile_size);
	mini_init(game);
	clear_minimap_image(game, game->mini.size);
	scale_tiles.x = round((game->mini.size.x / game->mini.tile_size + 1) / 2);
	scale_tiles.y = round((game->mini.size.y / game->mini.tile_size + 1) / 2);
	tile_pos.x = playerx - scale_tiles.x;
	tile_pos.y = playery - scale_tiles.y;
	win_pos.x = game->mini.center.x - game->mini.tile_size * (playerx - floor(playerx) + scale_tiles.x);
	win_pos.y = game->mini.center.y - game->mini.tile_size * (playery - floor(playery) + scale_tiles.y);
	minimap_tiles(*game, tile_pos, win_pos);
	draw_miniframe(game);
	draw_circle_mlx(game, game->mini.center, 0xFF0000);
}

int	draw_minimap(t_game *game)
{
	draw_minimap_loop(game, game->player.posx, game->player.posy);
	return (0);
}
