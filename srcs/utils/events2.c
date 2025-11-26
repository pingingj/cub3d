#include "../../incs/cub3d.h"

// int	close_door(t_pos new, double x, double y, t_game *game)
// {
// 	if (game->map.grid[(int)new.y][(int)new.x] == 'D'
// 		&& game->meth.looking_door == true)
// 	{
// 		game->map.grid[(int)new.y][(int)new.x] = 'd';
// 		if (hit_box(game, x, y, 1) == false || (game->ass.enemy.cords.x != -1
// 				&& hit_box(game, game->ass.enemy.cords.x,
// 					game->ass.enemy.cords.y, 0) == false))
// 		{
// 			game->map.grid[(int)new.y][(int)new.x] = 'D';
// 			return (0);
// 		}
// 		return (1);
// 	}
// 	return (2);
// }

void	start_timer(t_game *game, int x, int y)
{
	add_backdoor(&game->doors_opened, ft_newdoor(x, y));
}

void	door_timer(t_game *game)
{
	struct timeval	now;
	double			now_s;
	double			timer;
	t_door			*doors;

	gettimeofday(&now, NULL);
	now_s = (now.tv_sec) + (now.tv_usec / 1000000.0);
	timer = 5;
	doors = game->doors_opened;
	while (doors != NULL)
	{
		if (now_s - doors->open_s >= timer)
		{
			game->map.grid[doors->cords.y][doors->cords.x] = 'd';
			if (hit_box(game, game->player.posx, game->player.posy, 1) == false
				|| (game->ass.enemy.cords.x != -1 && hit_box(game,
						game->ass.enemy.cords.x, game->ass.enemy.cords.y,
						0) == false))
				game->map.grid[doors->cords.y][doors->cords.x] = 'D';
			else
			{
				doors->to_delete = true;
				delete_door_node(&game->doors_opened);
				break;
			}
		}
		doors = doors->next;
	}
}

bool	open_door(t_game *game, double x, double y)
{
	int		i;
	t_pos	new;
	double	angle;

	i = 0;
	while (i < ANGLE_NUMBERS)
	{
		angle = (2 * PI / ANGLE_NUMBERS) * i;
		new.x = x + cos(angle) * 0.4;
		new.y = y + sin(angle) * 0.4;
		if (game->map.grid[(int)new.y][(int)new.x] == 'd'
			&& game->meth.looking_door == true)
		{
			game->map.grid[(int)new.y][(int)new.x] = 'D';
			start_timer(game, (int)new.x, (int)new.y);
			return (true);
		}
		i++;
	}
	return (false);
}
