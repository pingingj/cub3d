#include "../../incs/cub3d.h"


bool	open_door(t_game *game, double x, double y)
{
	int		i;
	t_pos new;
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
			create_frame(game);
			return (true);
		}
        if (game->map.grid[(int)new.y][(int)new.x] == 'D'
			&& game->meth.looking_door == true)
		{
			game->map.grid[(int)new.y][(int)new.x] = 'd';
			if (hit_box(game, x, y) == false || (game->ass.enemy.cords.x != -1
					&& hit_box(game, game->ass.enemy.cords.x,
						game->ass.enemy.cords.y) == false))
			{
				game->map.grid[(int)new.y][(int)new.x] = 'D';
				return (false);
			}
			create_frame(game);
			return (true);
		}
		i++;
	}
	return (false);
}
