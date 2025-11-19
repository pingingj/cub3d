/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:50:26 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/19 15:03:55 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	has_line_of_sight(double ex, double ey, double px, double py)
{
	t_point	xy;
	t_point	endxy;
	t_point	d;
	t_point	s;
	int		err;
	int		e2;
	t_game	*game;

	game = mem_save(NULL);
	xy.x = (int)ex;
	xy.y = (int)ey;
	endxy.x = (int)px;
	endxy.y = (int)py;
	d.x = abs(endxy.x - xy.x);
	d.y = abs(endxy.y - xy.y);
	if (xy.x < endxy.x)
		s.x = 1;
	else
		s.x = -1;
	if (xy.y < endxy.y)
		s.y = 1;
	else
		s.y = -1;
	err = d.x - d.y;
	while (xy.x != endxy.x || xy.y != endxy.y)
	{
		if (xy.y >= 0 && xy.y < game->map.pos.y && xy.x >= 0
			&& xy.x < (int)ft_strlen(game->map.grid[xy.y])
			&& game->map.grid[xy.y][xy.x] == '1')
			return (0);
		e2 = 2 * err;
		if (e2 > -d.y)
		{
			err -= d.y;
			xy.x += s.x;
		}
		if (e2 < d.x)
		{
			err += d.x;
			xy.y += s.y;
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
		if (path_cell.x == next_cell.x && path_cell.y == next_cell.y)
			break ;
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
	double	speed;
	int		can_direct_chase;
	t_point	path_cell;
	double	move_x;
	double	move_y;

	path_cell = pathfinding_alg(game);
	can_direct_chase = !is_near_wall(game, game->ass.enemy.cords.x,
			game->ass.enemy.cords.y)
		&& has_line_of_sight(game->ass.enemy.cords.x, game->ass.enemy.cords.y,
			game->player.posx, game->player.posy);
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
	if (game->g_flags.collectibles_exist && game->ass.collect_amount
		- 1 != game->collected_comics)
		speed = (MONSTER_SPEED / ((game->ass.collect_amount - 1)
					- game->collected_comics));
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
			game->ass.sprites[game->ass.collect_amount
				- 1].cords.x = game->ass.enemy.cords.x;
			game->ass.sprites[game->ass.collect_amount
				- 1].cords.y = game->ass.enemy.cords.y;
		}
	}
	else
		game->g_flags.game_state = death_screen;
	return (0);
}
