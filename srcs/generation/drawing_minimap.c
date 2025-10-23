/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:15:34 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/23 15:52:05 by dgarcez-         ###   ########.fr       */
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


/* --- add near the top or in a common header --- */
static int	is_blocking_tile_char(char c)
{
	/* Treat solid walls and closed doors as blocking; tweak as needed */
	return (c == '1' || c == 'D' || c == 'd');
}

static int	is_blocking_cell(const t_game *g, int mx, int my)
{
	if (my < 0 || my >= (int)g->map.pos.y || mx < 0 || mx >= (int)g->map.pos.x)
		return 1; /* out of bounds: stop the ray */
	return is_blocking_tile_char(g->map.grid[my][mx]);
}

/* Clip a point into the minimap rectangle; returns 1 if inside, 0 if outside */
static int	in_minimap_rect(const t_game *g, int x, int y)
{
	int left   = g->mini.offset;
	int top    = g->mini.offset;
	int right  = g->mini.offset + g->mini.size.x - 1;
	int bottom = g->mini.offset + g->mini.size.y - 1;
	return (x >= left && x <= right && y >= top && y <= bottom);
}

/* Safe put pixel (clip to minimap rect) */
static inline void mini_put_px(t_game *g, int x, int y, int color)
{
	if (in_minimap_rect(g, x, y))
		my_mlx_pixel_put(&g->bg_img, x, y, color);
}

/* Bresenham line with minimap-rect clipping on every point */
static void	draw_line_minimap(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	while (1)
	{
		mini_put_px(game, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
}

/* Local, self-contained DDA cast that returns a safe, positive distance */
static double	cast_ray_minimap(const t_game *g, double camerax, double max_tiles)
{
	const double posx = g->player.posx;
	const double posy = g->player.posy;
	const double rdx  = g->player.dirx + g->player.planex * camerax;
	const double rdy  = g->player.diry + g->player.planey * camerax;

	/* Avoid zero division; huge = “infinite” */
	const double huge = 1e30;
	const double ddx  = (rdx == 0.0) ? huge : fabs(1.0 / rdx);
	const double ddy  = (rdy == 0.0) ? huge : fabs(1.0 / rdy);

	int mapx = (int)posx;
	int mapy = (int)posy;

	int stepx = (rdx < 0.0) ? -1 : 1;
	int stepy = (rdy < 0.0) ? -1 : 1;

	double sideX = (rdx < 0.0) ? (posx - mapx) * ddx : (mapx + 1.0 - posx) * ddx;
	double sideY = (rdy < 0.0) ? (posy - mapy) * ddy : (mapy + 1.0 - posy) * ddy;

	int hit = 0;
	int side = 0;

	/* Walk the grid until hit or we exceed an envelope around the minimap radius */
	const double guard = max_tiles + 2.0;
	while (!hit)
	{
		if (sideX < sideY) { sideX += ddx; mapx += stepx; side = 0; }
		else               { sideY += ddy; mapy += stepy; side = 1; }

		if (is_blocking_cell(g, mapx, mapy))
			hit = 1;

		/* Bail out if we wander too far; prevents infinite walk on open maps */
		if (fabs(mapx - posx) > guard || fabs(mapy - posy) > guard)
			break;
	}

	double dist;
	if (hit)
	{
		if (side == 0)
			dist = (mapx - posx + (1 - stepx) * 0.5) / (rdx == 0.0 ? 1e-9 : rdx);
		else
			dist = (mapy - posy + (1 - stepy) * 0.5) / (rdy == 0.0 ? 1e-9 : rdy);
	}
	else
	{
		/* No hit: limit to minimap radius */
		dist = max_tiles;
	}

	/* Ensure forward, finite, positive distance */
	if (!(dist > 0.0) || !isfinite(dist))
		dist = max_tiles;

	if (dist > max_tiles)
		dist = max_tiles;

	return dist;
}

/* Public: draws a fan of rays using the same logic as your raycaster */
void	draw_minimap_fov(t_game *game)
{
	/* Use your screen width for identical sampling as the 3D renderer */
	const int samples = WIDTH; /* or a smaller number if you want fewer rays */

	/* Minimap radius in tiles (so we don’t draw outside the frame) */
	double tiles_half_w = (game->mini.size.x / (double)game->mini.tile_size) * 0.5;
	double tiles_half_h = (game->mini.size.y / (double)game->mini.tile_size) * 0.5;
	double max_tiles = tiles_half_w < tiles_half_h ? tiles_half_w : tiles_half_h;
	if (max_tiles < 1.0)
		max_tiles = 1.0;

	const int x0 = (int)game->mini.center.x;
	const int y0 = (int)game->mini.center.y;

	for (int i = 0; i < samples; ++i)
	{
		/* Match your main raycaster’s formula exactly.
		   If your main loop uses: camerax = 2*x/(double)WIDTH - 1, do the same here. */
		double camerax = 2.0 * i / (double)(samples) - 1.0;

		double dist = cast_ray_minimap(game, camerax, max_tiles);

		double rdx = game->player.dirx + game->player.planex * camerax;
		double rdy = game->player.diry + game->player.planey * camerax;

		double endx = game->player.posx + rdx * dist;
		double endy = game->player.posy + rdy * dist;

		int x1 = (int)(game->mini.center.x + (endx - game->player.posx) * game->mini.tile_size);
		int y1 = (int)(game->mini.center.y + (endy - game->player.posy) * game->mini.tile_size);

		/* 24-bit RGB (yellow). Avoid ARGB like 0x66FFFF00 unless your put-pixel supports alpha. */
		draw_line_minimap(game, x0, y0, x1, y1, 0xFFFF00);
	}
}

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
	draw_minimap_fov(game);
}

int	draw_minimap(t_game *game)
{
	draw_minimap_loop(game, game->player.posx, game->player.posy);
	return (0);
}
