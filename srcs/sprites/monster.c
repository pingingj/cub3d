/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:50:26 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/18 16:36:45 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	has_line_of_sight(t_game *game, double ex, double ey, double px, double py)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	x = (int)ex;
	y = (int)ey;
	end_x = (int)px;
	end_y = (int)py;
	dx = abs(end_x - x);
	dy = abs(end_y - y);
	err = dx - dy;
	if (x < end_x)
		sx = 1;
	else
		sx = -1;
	if (y < end_y)
		sy = 1;
	else
		sy = -1;
	while (x != end_x || y != end_y)
	{
		if (y >= 0 && y < game->map.pos.y && x >= 0
			&& x < (int)ft_strlen(game->map.grid[y])
			&& game->map.grid[y][x] == '1')
			return (0);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
	return (1);
}

int	is_near_wall(t_game *game, double x, double y)
{
	int	cx;
	int	cy;
	int	dx[4] = {0, 0, -1, 1};
	int	dy[4] = {-1, 1, 0, 0};
	int	i;
	int	nx;
	int	ny;

	cx = (int)x;
	cy = (int)y;
	i = 0;
	while (i < 4)
	{
		nx = cx + dx[i];
		ny = cy + dy[i];
		if (ny >= 0 && ny < game->map.pos.y && nx >= 0
			&& nx < (int)ft_strlen(game->map.grid[ny])
			&& (game->map.grid[ny][nx] == '1' || game->map.grid[ny][nx] == 'd'))
			return (1);
		i++;
	}
	return (0);
}

t_point	pathfinding_alg(t_game *game)
{
	t_point	path_cell;
	t_point	next_cell;

	game->queue = monster_bfs_set_up(game);
	check_space(game, game->queue);
	path_cell.x = (int)game->player.posx;
	path_cell.y = (int)game->player.posy;
	next_cell = game->prev[path_cell.y][path_cell.x];
	while (!(next_cell.x == (int)game->ass.enemy.cords.x
			&& next_cell.y == (int)game->ass.enemy.cords.y))
	{
		path_cell.x = next_cell.x;
		path_cell.y = next_cell.y;
		next_cell = game->prev[path_cell.y][path_cell.x];
		if(path_cell.x == next_cell.x && path_cell.y == next_cell.y)
			break;
	}
	free_queue(game->queue);
	return (path_cell);
}

int	monster(t_game *game)
{
	double	target_cx;
	double	target_cy;
	double	dx;
	double	dy;
	double	dist;
	double speed;
	int		can_direct_chase;
	t_point	path_cell;
	double	move_x;
	double	move_y;

	path_cell = pathfinding_alg(game);
	can_direct_chase = !is_near_wall(game, game->ass.enemy.cords.x,
			game->ass.enemy.cords.y) && has_line_of_sight(game,
			game->ass.enemy.cords.x, game->ass.enemy.cords.y, game->player.posx,
			game->player.posy);
	if (can_direct_chase)
	{
		dx = game->player.posx - game->ass.enemy.cords.x;
		dy = game->player.posy - game->ass.enemy.cords.y;
	}
	else
	{
		target_cx = path_cell.x + 0.5;
		target_cy = path_cell.y + 0.5;
		dx = target_cx - game->ass.enemy.cords.x;
		dy = target_cy - game->ass.enemy.cords.y;
	}
	dist = sqrt(dx * dx + dy * dy);
	if(game->g_flags.collectibles_exist && game->ass.collect_amount - 1 != game->collected_comics)
		speed = (MONSTER_SPEED / ((game->ass.collect_amount - 1) - game->collected_comics));
	else
		speed = 0.09;
	if (dist > 0.5)
	{
		move_x = game->ass.enemy.cords.x + speed * (dx / dist);
		move_y = game->ass.enemy.cords.y + speed * (dy / dist);
		if (game->map.grid[(int)move_y][(int)move_x] != '1'
			&& game->map.grid[(int)move_y][(int)move_x] != 'd')
		{
			game->ass.enemy.cords.x = move_x;
			game->ass.enemy.cords.y = move_y;
			game->ass.sprites[game->ass.collect_amount- 1].cords.x = game->ass.enemy.cords.x;
			game->ass.sprites[game->ass.collect_amount- 1].cords.y = game->ass.enemy.cords.y;
		}
	}
	else
		game->g_flags.game_state = death_screen;
	return (0);
}
