/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_mini_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:38:50 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 16:40:26 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

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

void	get_tile(t_game game, char grid, t_pos win_cord, t_pos area)
{
	if (grid == '1')
		draw_tile(&game.bg_img, 0x9DD1E0, area, win_cord);
	else if (grid == 'd')
		draw_tile(&game.bg_img, 0x000089, area, win_cord);
	else if (grid == 'D')
		draw_tile(&game.bg_img, 0x8599BA, area, win_cord);
	else
		draw_tile(&game.bg_img, 0x223030, area, win_cord);
}

void	draw_minitile_row(t_game game, t_pos tile_pos, t_pos win_cord,
		t_pos area)
{
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
			get_tile(game, game.map.grid[(int)tile_pos.y][(int)tile_pos.x],
				win_cord, area);
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
