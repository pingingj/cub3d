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

// t_list *monster_bfs_set_up(t_game *game)
// {
// 	int y;
// 	t_point *monster_pt;
// 	t_list *queue;
// 	int row_length;
	
// 	queue = NULL;
// 	y = 0;
// 	while (y < game->map.height)
// 	{
// 		row_length = strlen(game->map.grid[y]);
// 		ft_bzero(game->visited[y], sizeof(int) * row_length);
// 		ft_bzero(game->parent[y], sizeof(t_point) * row_length);
// 		y++;
// 	}
// 	monster_pt = malloc(sizeof(t_point));
// 	monster_pt->x = (int)game->ass.enemy.cords.x;
// 	monster_pt->y = (int)game->ass.enemy.cords.y;
// 	ft_lstadd_back(&queue, ft_lstnew(monster_pt));
// 	game->visited[monster_pt->y][monster_pt->x] = 1;
// 	game->parent[monster_pt->y][monster_pt->x] = *monster_pt; 
// 	return(queue);
// }

// void check_space(t_game *game,t_list *q)
// {
// 	t_list *node;
// 	t_point *curr;
// 	int new_x;
// 	int new_y;
// 	int i;
// 	int dx[4] = {0, 0, -1, 1};
//     int dy[4] = {-1, 1, 0, 0};
	
// 	i = 0;
// 	while(q)
// 	{
// 		node = q;
// 		curr = q->content;
// 		q = q->next;
// 		while(i < 4)
// 		{
// 			new_x = new_x + dx[i];
// 			new_y = new_y + dy[i];
// 			if (new_y >= 0 && new_y < game->map.height && 
// 				new_x >= 0 && new_x < strlen(game->map.grid[ny]))
// 			{

// 			}
// 		}
// 	}
// }
// int monster(t_game *game)
// {
// 	t_list *queue;
	
// 	queue = monster_bfs_set_up(game);
// 	check_space(game,queue);
// 	return (0);
// }

// void  enemy(t_game *game)
// {
// 	int y; 
// 	int row_length;

// 	y = 0;
// 	game->visited = malloc(sizeof(int *) * game->map.height);
// 	game->parent = malloc(sizeof(t_point *) * game->map.height);
// 	game->ass.enemy.cords.x = 30;
// 	game->ass.enemy.cords.y = 19;
// 	while (y < game->map.height)
// 	{
// 		row_length = strlen(game->map.grid[y]);
// 		game->visited[y] = calloc(row_length, sizeof(int));
// 		game->parent[y] = malloc(sizeof(t_point) * row_length);
// 		y++;
// 	}
// }
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc == 2)
	{
		if (parse(&game, argv[1]) == false)
			return (1);
		game.mlx = mlx_init();
		print_info(game);
		textures(&game);
		// enemy(&game);
		map_gen(&game);
		mlx_hook(game.win, 17, 0, closex, &game);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 6, 1L << 6, mouse, &game);
		mlx_loop_hook(game.mlx, move, &game);
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
