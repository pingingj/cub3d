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

t_queue	*monster_bfs_set_up(t_game *game)
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

void	init_dirs(int *dx, int *dy)
{
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 1;
	dy[0] = -1;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = 0;
}

void	while_do(t_game *game, t_queue *q, t_point *curr, int i)
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

void	check_space(t_game *game, t_queue *q)
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
