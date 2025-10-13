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
				game->map.grid[new_y][new_x] != '1' && game->visited[new_y][new_x] == 0)
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

int	monster(t_game *game)
{
	double	target_cx;
	double	target_cy;
	double	dist_to_target;
	double	dx;
	double	dy;
	double	dist;
	t_point	path_cell;
	t_point	next_cell;
	t_list	*queue;

	target_cx = game->monster_target_x + 0.5;
	target_cy = game->monster_target_y + 0.5;
	dist_to_target = sqrt(
		(game->ass.enemy.cords.x - target_cx) * (game->ass.enemy.cords.x - target_cx) +
		(game->ass.enemy.cords.y - target_cy) * (game->ass.enemy.cords.y - target_cy)
	);
	if (!game->monster_has_target || dist_to_target < 0.05)
	{
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
		game->monster_target_x = path_cell.x;
		game->monster_target_y = path_cell.y;
		game->monster_has_target = 1;
		free_queue(queue);
		target_cx = game->monster_target_x + 0.5;
		target_cy = game->monster_target_y + 0.5;
		dist_to_target = sqrt(
			(game->ass.enemy.cords.x - target_cx) * (game->ass.enemy.cords.x - target_cx) +
			(game->ass.enemy.cords.y - target_cy) * (game->ass.enemy.cords.y - target_cy)
		);
	}
	dx = target_cx - game->ass.enemy.cords.x;
	dy = target_cy - game->ass.enemy.cords.y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 0.01)
	{
		game->ass.enemy.cords.x += MONSTER_SPEED * (dx / dist);
		game->ass.enemy.cords.y += MONSTER_SPEED * (dy / dist);
		game->ass.collectible[game->ass.collect_amount - 1].cords.x = game->ass.enemy.cords.x;
		game->ass.collectible[game->ass.collect_amount - 1].cords.y = game->ass.enemy.cords.y;
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
		row_length = strlen(game->map.grid[y]);
		game->visited[y] = calloc(row_length, sizeof(int));
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
