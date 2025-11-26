/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:15:34 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/11/25 15:06:10 by dgarcez-         ###   ########.fr       */
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

// void	draw_circle_mlx(t_game *game, int cx, int cy, int color)
// {
// 	int radius;
// 	int	x;
// 	int	y;

// 	radius = game->mini.tile_size / 6;
// 	y = cy - radius;
// 	while (y <= cy + radius)
// 	{
// 		x = cx - radius;
// 		while (x <= cx + radius)
// 		{
// 			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius
// 				* radius)
// 				my_mlx_pixel_put(&game->bg_img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

/* Minimap clipping helpers */
/* Signed area (edge function) you already have */
static inline int edge_fn(int ax, int ay, int bx, int by, int px, int py)
{
	return (px - ax) * (by - ay) - (py - ay) * (bx - ax);
}

/* Orientation-agnostic point-in-triangle */


/* Normalize 2D vector (you already have normalize2; keep one) */
static inline void normalize2(double *x, double *y)
{
	double len = sqrt((*x) * (*x) + (*y) * (*y));
	if (len > 1e-9) { *x /= len; *y /= len; }
}

void fill_triangle_minimap(t_game *g,
                           int ax, int ay,
                           int bx, int by,
                           int cx, int cy,
                           int color)
{
	/* Degenerate? (area == 0) */
	int area2 = edge_fn(ax, ay, bx, by, cx, cy);
	if (area2 == 0)
		return;

	/* Bounding box (then clip to minimap rect) */
	int minX = ax; if (bx < minX) minX = bx; if (cx < minX) minX = cx;
	int maxX = ax; if (bx > maxX) maxX = bx; if (cx > maxX) maxX = cx;
	int minY = ay; if (by < minY) minY = by; if (cy < minY) minY = cy;
	int maxY = ay; if (by > maxY) maxY = by; if (cy > maxY) maxY = cy;

	int left   = g->mini.offset;
	int top    = g->mini.offset;
	int right  = g->mini.offset + g->mini.size.x - 1;
	int bottom = g->mini.offset + g->mini.size.y - 1;

	if (minX < left)   minX = left;
	if (maxX > right)  maxX = right;
	if (minY < top)    minY = top;
	if (maxY > bottom) maxY = bottom;

	/* Accept rule based on winding */
	int ccw = (area2 > 0);

	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			int w0 = edge_fn(ax, ay, bx, by, x, y);
			int w1 = edge_fn(bx, by, cx, cy, x, y);
			int w2 = edge_fn(cx, cy, ax, ay, x, y);

			if (ccw)
			{
				if (w0 >= 0 && w1 >= 0 && w2 >= 0)
					my_mlx_pixel_put(&g->bg_img, x, y, color);
			}
			else
			{
				if (w0 <= 0 && w1 <= 0 && w2 <= 0)
					my_mlx_pixel_put(&g->bg_img	, x, y, color);
			}
		}
	}
}

/*
Chevron arrow:
- Outer triangle (tip forward) minus inner notch triangle (base-side cut)
- Everything drawn in a single color (solid red).
*/
void	draw_arrow(t_game *game, int cx, int cy, int color)
{
	/* Forward and perpendicular */
	double fx = game->player.dirx;
	double fy = game->player.diry;
	normalize2(&fx, &fy);
	double px = -fy, py = fx;

	/* Scale knobs (in pixels) */
	double T          = game->mini.tile_size * 0.8;
	double tip_len    = 0.45 * T;  /* tip distance forward */
	double base_len   = 0.50 * T;  /* where left/right sit behind center */
	double apex_len   = 0.20 * T;  /* bottom apex; bigger -> lower (further back) */
	double arm_half   = 0.45 * T;  /* half width at the “base” spread */

	/* Points (float) */
	double tipx = cx + fx * tip_len;
	double tipy = cy + fy * tip_len;

	double lx   = cx - fx * base_len + px * arm_half;
	double ly   = cy - fy * base_len + py * arm_half;

	double rx   = cx - fx * base_len - px * arm_half;
	double ry   = cy - fy * base_len - py * arm_half;

	double ax   = cx - fx * apex_len; /* lower bottom apex */
	double ay   = cy - fy * apex_len;

	/* Convert to ints (use same rounding for both triangles so edges align) */
	int T_x = (int)lround(tipx), T_y = (int)lround(tipy);
	int L_x = (int)lround(lx),   L_y = (int)lround(ly);
	int R_x = (int)lround(rx),   R_y = (int)lround(ry);
	int A_x = (int)lround(ax),   A_y = (int)lround(ay);

	/* Fill two arms; no horizontal base is drawn */
	fill_triangle_minimap(game, T_x, T_y, L_x, L_y, A_x, A_y, color);
	fill_triangle_minimap(game, T_x, T_y, A_x, A_y, R_x, R_y, color);
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
				draw_tile(&game.bg_img, 0x000089, area, win_cord);
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
				my_mlx_pixel_put(&game->bg_img, x, y, 0x9900BB);
			if (y < game->mini.offset + 10 || y > game->mini.size.y + 20)
				my_mlx_pixel_put(&game->bg_img, x, y, 0x9900BB);
			x++;
		}
		y++;
	}
}
void	draw_minimap(t_game *game, double playerx, double playery)
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
	draw_arrow(game, game->mini.center.x, game->mini.center.y, 0xFF0000);
	// draw_circle_mlx(game, (int)game->mini.center.x, (int)game->mini.center.y, 0xFF0000);
}
