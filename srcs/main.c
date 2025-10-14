/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/02 17:11:21 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	mouse(int x, int y, t_game *game)
{
	game->mouse.x = x - WIDTH / 2;
	if (x > WIDTH / 2)
		game->move[4] = 1;
	if (x < WIDTH / 2)
		game->move[5] = 1;
	if (x == WIDTH / 2)
	{
		game->move[4] = 0;
		game->move[5] = 0;
	}
	game->mouse.y = y - HEIGHT / 2;
	if (y > HEIGHT / 2)
	{
		game->player.look -= game->mouse.y/10;
		if(game->player.look < -1000)
			game->player.look +=game->mouse.y/10;
	}
	if (y < HEIGHT / 2)
	{
		game->player.look += -game->mouse.y/10;
		if(game->player.look > 1000)
			game->player.look -= -game->mouse.y/10;
	}
	if (x != WIDTH / 2 || y != HEIGHT / 2)
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

t_list *monster_bfs_set_up(t_game *game)
{
	int y;
	t_point *monster_pt;
	t_list *queue;
	int row_length;
	
	queue = NULL;
	y = 0;
	while (y < game->map.pos.y)
	{
		row_length = strlen(game->map.grid[y]);
		ft_bzero(game->visited[y], sizeof(int) * row_length);
		ft_bzero(game->prev[y], sizeof(t_point) * row_length);
		y++;
	}
	monster_pt = malloc(sizeof(t_point));
	monster_pt->x = (int)game->ass.enemy.cords.x;
	monster_pt->y = (int)game->ass.enemy.cords.y;
	if (monster_pt->y >= 0 && monster_pt->y < game->map.pos.y && monster_pt->x >= 0 && monster_pt->x < (int)strlen(game->map.grid[monster_pt->y]))
	{
		ft_lstadd_back(&queue, ft_lstnew(monster_pt));
		game->visited[monster_pt->y][monster_pt->x] = 1;
		game->prev[monster_pt->y][monster_pt->x] = *monster_pt;
	}
	return(queue);
}

void check_space(t_game *game,t_list *q)
{
	// t_list *node;
	t_point *curr;
	t_point *next;
	int new_x;
	int new_y;
	int i;
	int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
	
	while(q)
	{
		// node = q;
		curr = q->content;
		q = q->next;
		i = 0;
		while(i < 4)
		{
			new_x = curr->x + dx[i];
			new_y = curr->y + dy[i];
			if (new_y >= 0 && new_y < game->map.pos.y && 
				new_x >= 0 && new_x < (int)strlen(game->map.grid[new_y]) && 
				game->map.grid[new_y][new_x] != '1' && game->map.grid[new_y][new_x] != 'd'  && game->visited[new_y][new_x] == 0)
			{
					game->visited[new_y][new_x] = 1;
					game->prev[new_y][new_x] = *curr;
					next = malloc(sizeof(t_point));
					next->x = new_x;
					next->y = new_y;
					ft_lstadd_back(&q, ft_lstnew(next));
			}
			i++;
		}
	}
}

void free_queue(t_list *queue)
{
    t_list *tmp;
    while (queue)
    {
        tmp = queue->next;
        free(queue->content); // free monster_pt or next
        free(queue);          // free the list node itself
        queue = tmp;
    }
}

// Returns 1 if there is a clear line of sight from (x0, y0) to (x1, y1) (no walls '1' between)
// All coordinates are grid positions (you can cast your float positions to int)
int has_line_of_sight(t_game *game, double x0, double y0, double x1, double y1)
{
	int x = (int)x0;
	int y = (int)y0;
	int end_x = (int)x1;
	int end_y = (int)y1;
	int dx = abs(end_x - x);
	int dy = abs(end_y - y);
	int sx = x < end_x ? 1 : -1;
	int sy = y < end_y ? 1 : -1;
	int err = dx - dy;

	while (x != end_x || y != end_y)
	{
		// If in bounds, check for wall
		if (y >= 0 && y < game->map.pos.y &&
			x >= 0 && x < (int)strlen(game->map.grid[y]) &&
			game->map.grid[y][x] == '1')
			return 0;
		int e2 = 2 * err;
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
	return 1;
}

int is_near_wall(t_game *game, double x, double y)
{
	int cx = (int)x;
	int cy = (int)y;
	int dx[4] = {0, 0, -1, 1};
	int dy[4] = {-1, 1, 0, 0};
	for (int i = 0; i < 4; ++i) {
		int nx = cx + dx[i];
		int ny = cy + dy[i];
		if (ny >= 0 && ny < game->map.pos.y &&
			nx >= 0 && nx < (int)strlen(game->map.grid[ny]) &&
			game->map.grid[ny][nx] == '1')
			return 1;
	}
	return 0;
}

int	monster(t_game *game)
{
	double target_cx, target_cy, dx, dy, dist;
	t_list *queue;
	t_point path_cell, next_cell;

	// BFS setup
	queue = monster_bfs_set_up(game);
	check_space(game, queue);

	path_cell.x = (int)game->player.posx;
	path_cell.y = (int)game->player.posy;
	next_cell = game->prev[path_cell.y][path_cell.x];
	while (!(next_cell.x == (int)game->ass.enemy.cords.x &&
			 next_cell.y == (int)game->ass.enemy.cords.y))
	{
		path_cell.x = next_cell.x;
		path_cell.y = next_cell.y;
		next_cell = game->prev[path_cell.y][path_cell.x];
	}
	free_queue(queue);

	// --- Hybrid logic ---
	int can_direct_chase = !is_near_wall(game, game->ass.enemy.cords.x, game->ass.enemy.cords.y) &&
		has_line_of_sight(game, game->ass.enemy.cords.x, game->ass.enemy.cords.y,
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
	if (dist > 0.01)
	{
		double move_x = game->ass.enemy.cords.x + MONSTER_SPEED * (dx / dist);
		double move_y = game->ass.enemy.cords.y + MONSTER_SPEED * (dy / dist);

		if (game->map.grid[(int)move_y][(int)move_x] != '1' && game->map.grid[(int)move_y][(int)move_x] != 'd')
		{
			game->ass.enemy.cords.x = move_x;
			game->ass.enemy.cords.y = move_y;
			game->ass.collectible[game->ass.collect_amount - 1].cords.x = game->ass.enemy.cords.x;
			game->ass.collectible[game->ass.collect_amount - 1].cords.y = game->ass.enemy.cords.y;
		}
	}
	return (0);
}

void  enemy(t_game *game)
{
	int y; 
	int row_length;

	y = 0;
	game->visited = malloc(sizeof(int *) * game->map.pos.y);
	game->prev = malloc(sizeof(t_point *) * game->map.pos.y);
	game->ass.enemy.cords.x = 30;
	game->ass.enemy.cords.y = 19;
	while (y < game->map.pos.y)
	{
		row_length = ft_strlen(game->map.grid[y]);
		game->visited[y] = ft_calloc(row_length, sizeof(int));
		game->prev[y] = malloc(sizeof(t_point) * row_length);
		y++;
	}
}
int main_loop(t_game *game)
{
	move(game);
	monster(game);
	create_frame(game);
	return (0);
}
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc == 2)
	{
		if (parse(&game, argv[1]) == false)
			return (1);
		game.mlx = mlx_init();
		// print_info(game);
		textures(&game);
		enemy(&game);
		map_gen(&game);
		mlx_hook(game.win, 17, 0, closex, &game);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 6, 1L << 6, mouse, &game);
		mlx_loop_hook(game.mlx, main_loop, &game);
		// mlx_loop_hook(game.mlx, monster, &game);
		mlx_mouse_hide(game.mlx, game.win);
		mlx_loop(game.mlx);
		free_game(&game);
		return (1);
	}
	else
		return (print_errors(&game, 1, "Not valid amount of arguments", -1), 1);
	return (0);
}
