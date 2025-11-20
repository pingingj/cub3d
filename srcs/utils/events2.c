#include "../../incs/cub3d.h"


int	close_door(t_pos new, double x, double y, t_game *game)
{
	if (game->map.grid[(int)new.y][(int)new.x] == 'D'
		&& game->meth.looking_door == true)
	{
		game->map.grid[(int)new.y][(int)new.x] = 'd';
		if (hit_box(game, x, y,1) == false || (game->ass.enemy.cords.x != -1
				&& hit_box(game, game->ass.enemy.cords.x,
					game->ass.enemy.cords.y,0) == false))
		{
			game->map.grid[(int)new.y][(int)new.x] = 'D';
			return (0);
		}
		return (1);
	}
	return (2);
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
			return (true);
		}
		int h = close_door(new, x, y, game);
		if (h == 0)
			return (false);
		else if (h== 1)
			return (true);
		i++;
	}
	return (false);
}

// bool	open_door(t_game *game, double x, double y)
// {
// 	int		i;
// 	t_pos	new;
// 	double	angle;

// 	i = 0;
// 	while (i < ANGLE_NUMBERS)
// 	{
// 		angle = (2 * PI / ANGLE_NUMBERS) * i;
// 		new.x = x + cos(angle) * 0.4;
// 		new.y = y + sin(angle) * 0.4;
// 		if (game->map.grid[(int)new.y][(int)new.x] == 'd'
// 			&& game->meth.looking_door == true)
// 		{
// 			game->map.grid[(int)new.y][(int)new.x] = 'D';
// 			return (true);
// 		}
// 		if (game->map.grid[(int)new.y][(int)new.x] == 'D'
// 			&& game->meth.looking_door == true)
// 		{
// 			game->map.grid[(int)new.y][(int)new.x] = 'd';
// 			if (hit_box(game, x, y) == false || (game->ass.enemy.cords.x != -1
// 					&& hit_box(game, game->ass.enemy.cords.x,
// 						game->ass.enemy.cords.y) == false))
// 			{
// 				game->map.grid[(int)new.y][(int)new.x] = 'D';
// 				return (false);
// 			}
// 			return (true);
// 		}
// 		i++;
// 	}
// 	return (false);
// }
