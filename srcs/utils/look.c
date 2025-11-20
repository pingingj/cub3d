#include "../../incs/cub3d.h"

/*to lookj in both direction i use a formula that rotates vectors,
	since for the camere i have the direction and the plane (fov)
	i need to rotate both, but thats just it*/
void	look_right(t_game *game)
{
	double	old_dirx;
	double	old_planex;
	double angle;
	int x;

	x= 1;
	angle = ARROW_ROT_SPEED;
	if(game->g_flags.look_flag_right == false)
	{
		x = game->mouse.x;
		angle = ROT_SPEED;
	}
	old_dirx = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(x * angle) - game->player.diry
		* sin(x * angle);
	game->player.diry = old_dirx * sin(x * angle) + game->player.diry
		* cos(x * angle);
	old_planex = game->player.planex;
	game->player.planex = game->player.planex * cos(x * angle)
		- game->player.planey * sin(x * angle);
	game->player.planey = old_planex * sin(x * angle) + game->player.planey
		* cos(x * angle);
}
void	look_left(t_game *game)
{
	double	old_dirx;
	double	old_planex;
	double	angle;
	int		x;

	x = -1;
	angle = ARROW_ROT_SPEED;
	if (game->g_flags.look_flag_left == false)
	{
		x = game->mouse.x;
		angle = ROT_SPEED;
	}
	old_dirx = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(x * angle) - game->player.diry
		* sin(x * angle);
	game->player.diry = old_dirx * sin(x * angle) + game->player.diry * cos(x
			* angle);
	old_planex = game->player.planex;
	game->player.planex = game->player.planex * cos(x * angle)
		- game->player.planey * sin(x * angle);
	game->player.planey = old_planex * sin(x * angle) + game->player.planey
		* cos(x * angle);
}
