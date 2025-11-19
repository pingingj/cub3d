/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_pathfinding.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:52:01 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/19 15:44:05 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static t_queue	*monster_bfs_set_up(t_game *game)
{
	int		y;
	t_point	*monster_pt;
	t_queue	*queue;
	int		row_length;

	queue = NULL;
	y = -1;
	while (++y < game->map.pos.y)
	{
		row_length = ft_strlen(game->map.grid[y]);
		ft_bzero(game->visited[y], sizeof(int) * row_length);
		ft_bzero(game->prev[y], sizeof(t_point) * row_length);
	}
	monster_pt = malloc(sizeof(t_point));
	monster_pt->x = (int)game->ass.enemy.cords.x;
	monster_pt->y = (int)game->ass.enemy.cords.y;
	if (monster_pt->y >= 0 && monster_pt->y < game->map.pos.y
		&& monster_pt->x >= 0
		&& monster_pt->x < (int)ft_strlen(game->map.grid[monster_pt->y]))
	{
		ft_queueadd_back(&queue, ft_queuenew(monster_pt));
		game->visited[monster_pt->y][monster_pt->x] = 1;
		game->prev[monster_pt->y][monster_pt->x] = *monster_pt;
	}
	return (queue);
}

static void	while_do(t_game *game, t_queue *q, t_point *curr, int i)
{
	int		new_x;
	int		new_y;
	t_point	*next;
	int		dx[4];
	int		dy[4];

	init_dirs(dx, dy);
	new_x = curr->x + dx[i];
	new_y = curr->y + dy[i];
	if (new_y >= 0 && new_y < game->map.pos.y && new_x >= 0
		&& new_x < (int)ft_strlen(game->map.grid[new_y])
		&& game->map.grid[new_y][new_x] != '1'
		&& game->map.grid[new_y][new_x] != 'd'
		&& game->visited[new_y][new_x] == 0)
	{
		game->visited[new_y][new_x] = 1;
		game->prev[new_y][new_x] = *curr;
		next = ft_calloc(1, sizeof(t_point));
		next->x = new_x;
		next->y = new_y;
		ft_queueadd_back(&q, ft_queuenew(next));
	}
}

static void	check_space(t_game *game, t_queue *q)
{
	t_point	*curr;
	int		i;

	while (q)
	{
		curr = q->content;
		i = -1;
		while (++i < 4)
		{
			while_do(game, q, curr, i);
		}
		q = q->next;
	}
}

static t_point	pathfinding_alg(t_game *game)
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

void choose_pathfinding_alg(t_game *game,t_pos target,t_pos *d)
{
	t_point	path_cell;
	int		can_direct_chase;

	can_direct_chase = !is_near_wall(game, game->ass.enemy.cords.x,
			game->ass.enemy.cords.y)
		&& has_line_of_sight(game->ass.enemy.cords.x, game->ass.enemy.cords.y,
			game->player.posx, game->player.posy);
	if (can_direct_chase)
	{
		d->x = game->player.posx - game->ass.enemy.cords.x;
		d->y = game->player.posy - game->ass.enemy.cords.y;
	}
	else
	{
		path_cell = pathfinding_alg(game);
		target.x = path_cell.x + 0.5;
		target.y = path_cell.y + 0.5;
		d->x = target.x - game->ass.enemy.cords.x;
		d->y = target.y - game->ass.enemy.cords.y;
	}
}