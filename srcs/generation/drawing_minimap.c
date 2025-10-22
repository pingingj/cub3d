/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:15:34 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/22 14:43:41 by dgarcez-         ###   ########.fr       */
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

void	draw_circle_mlx(t_game *game, int cx, int cy, int color)
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
			else if (grid == 'c')
				draw_tile(&game.bg_img, 0x223030, area, win_cord);
			else if (grid == 'j')
				draw_tile(&game.bg_img, 0x223030, area, win_cord);
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

// static void draw_line_minimap(t_game *game, int x0, int y0, int x1, int y1, int color)
// {
// 	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
// 	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
// 	int err = dx + dy, e2;

// 	while (1)
// 	{
// 		my_mlx_pixel_put(&game->bg_img, x0, y0, color);
// 		if (x0 == x1 && y0 == y1) 
// 			break;
// 		e2 = 2 * err;
// 		if (e2 >= dy) 
// 		{
// 			err += dy; x0 += sx;
// 		}
// 		if (e2 <= dx) 
// 		{
// 			err += dx; y0 += sy;
// 		}
// 	}
// }

// void draw_minimap_fov(t_game *game)
// {
// 	// How many rays to cast in the mini FOV
// 	const int samples = 120;

// 	// Half-width of minimap window in tiles (approx radius to stop rays)
// 	double tiles_half_w = (game->mini.size.x / (double)game->mini.tile_size) * 0.5;
// 	double tiles_half_h = (game->mini.size.y / (double)game->mini.tile_size) * 0.5;
// 	double max_tiles = tiles_half_w < tiles_half_h ? tiles_half_w : tiles_half_h;
// 	if (max_tiles < 1.0) max_tiles = 1.0;

// 	// Player cell start
// 	game->meth.mapx = (int)game->player.posx;
// 	game->meth.mapy = (int)game->player.posy;

// 	for (int i = 0; i < samples; ++i)
// 	{
// 		// Sweep across FOV using camera plane, same formula as setup_ray()
// 		double camerax = 2.0 * i / (samples - 1) - 1.0;
// 		game->meth.raydirx = game->player.dirx + game->player.planex * camerax;
// 		game->meth.raydiry = game->player.diry + game->player.planey * camerax;

// 		// Prepare DDA and cast
// 		dda_prep(game);
// 		(void)hit_wall(game); // updates meth.mapx/mapy and sets door/orientation as needed
// 		double walldist = calc_wall_dist(game);

// 		// Clamp to minimap radius in tiles so we don't draw outside the frame
// 		if (walldist > max_tiles) walldist = max_tiles;

// 		// World-space hit point (or clamped end)
// 		double endx = game->player.posx + game->meth.raydirx * walldist;
// 		double endy = game->player.posy + game->meth.raydiry * walldist;

// 		// Convert to minimap pixels
// 		int x0 = (int)game->mini.center.x;
// 		int y0 = (int)game->mini.center.y;
// 		int x1 = (int)(game->mini.center.x + (endx - game->player.posx) * game->mini.tile_size);
// 		int y1 = (int)(game->mini.center.y + (endy - game->player.posy) * game->mini.tile_size);

// 		// Draw the ray on the minimap (semi-transparent-ish color)
// 		draw_line_minimap(game, x0, y0, x1, y1, 0x66FFFF00);
// 	}
// }

void	draw_minimap_loop(t_game *game, double playerx, double playery)
{
	t_pos	scale_tiles;
	t_pos	tile_pos;
	t_pos	win_pos;
	
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
	draw_circle_mlx(game, (int)game->mini.center.x, (int)game->mini.center.y, 0xFF0000);
	// draw_minimap_fov(game);
}

int	draw_minimap(t_game *game)
{
	draw_minimap_loop(game, game->player.posx, game->player.posy);
	return (0);
}
