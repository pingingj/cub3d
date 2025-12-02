/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_arrow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:39:53 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 16:40:29 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	check_side(t_point a, t_point b, t_point point)
{
	return ((point.x - a.x) * (b.y - a.y) - (point.y - a.y) * (b.x - a.x));
}

void	min_max(t_point *min, t_point *max, t_point side, t_point bottom)
{
	if (side.x < min->x)
		min->x = side.x;
	if (bottom.x < min->x)
		min->x = bottom.x;
	if (side.x > max->x)
		max->x = side.x;
	if (bottom.x > max->x)
		max->x = bottom.x;
	if (side.y < min->y)
		min->y = side.y;
	if (bottom.y < min->y)
		min->y = bottom.y;
	if (side.y > max->y)
		max->y = side.y;
	if (bottom.y > max->y)
		max->y = bottom.y;
}

void	fill_triangle_minimap(t_game *g, t_point tip, t_point side,
		t_point bottom)
{
	t_point	min;
	t_point	max;
	t_point	coords;
	int		angles[3];

	min.x = tip.x;
	min.y = tip.y;
	max.x = tip.x;
	max.y = tip.y;
	min_max(&min, &max, side, bottom);
	coords.y = min.y - 1;
	while (++coords.y <= max.y)
	{
		coords.x = min.x - 1;
		while (++coords.x <= max.x)
		{
			angles[0] = check_side(tip, side, coords);
			angles[1] = check_side(side, bottom, coords);
			angles[2] = check_side(bottom, tip, coords);
			if (angles[0] >= 0 && angles[1] >= 0 && angles[2] >= 0)
				my_mlx_pixel_put(&g->bg_img, coords.x, coords.y, 0xFF0000);
			if (angles[0] <= 0 && angles[1] <= 0 && angles[2] <= 0)
				my_mlx_pixel_put(&g->bg_img, coords.x, coords.y, 0xFF0000);
		}
	}
}

void	arrow_aux(t_game *game, t_arrow arrow)
{
	t_point	tip_p;
	t_point	left_p;
	t_point	right_p;
	t_point	bottom_p;

	tip_p.x = (int)arrow.tip.x;
	tip_p.y = (int)arrow.tip.y;
	left_p.x = (int)arrow.left.x;
	left_p.y = (int)arrow.left.y;
	right_p.x = (int)arrow.right.x;
	right_p.y = (int)arrow.right.y;
	bottom_p.x = (int)arrow.bottom.x;
	bottom_p.y = (int)arrow.bottom.y;
	fill_triangle_minimap(game, tip_p, left_p, bottom_p);
	fill_triangle_minimap(game, tip_p, right_p, bottom_p);
}

void	draw_arrow(t_game *game, int cx, int cy)
{
	t_arrow	arrow;

	arrow.size = game->mini.tile_size * 0.8;
	arrow.tip_len = 0.45 * arrow.size;
	arrow.base_len = 0.50 * arrow.size;
	arrow.bottom_len = 0.20 * arrow.size;
	arrow.sides_len = 0.45 * arrow.size;
	arrow.tip.x = cx + game->player.dirx * arrow.tip_len;
	arrow.tip.y = cy + game->player.diry * arrow.tip_len;
	arrow.left.x = cx - game->player.dirx * arrow.base_len
		+ (-game->player.diry) * arrow.sides_len;
	arrow.left.y = cy - game->player.diry * arrow.base_len + game->player.dirx
		* arrow.sides_len;
	arrow.right.x = cx - game->player.dirx * arrow.base_len
		- (-game->player.diry) * arrow.sides_len;
	arrow.right.y = cy - game->player.diry * arrow.base_len - game->player.dirx
		* arrow.sides_len;
	arrow.bottom.x = cx - game->player.dirx * arrow.bottom_len;
	arrow.bottom.y = cy - game->player.diry * arrow.bottom_len;
	arrow_aux(game, arrow);
}
