/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:15 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/21 19:32:54 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	background_gen(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "NEETs");
	game->bg_img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->bg_img.addr = mlx_get_data_addr(game->bg_img.img,
			&game->bg_img.bits_per_pixel, &game->bg_img.line_length,
			&game->bg_img.endian);
	// game->mini_map.img = mlx_new_image(game->mlx, 200, 200);
	// game->mini_map.addr = mlx_get_data_addr(game->mini_map.img,
	// 		&game->mini_map.bits_per_pixel, &game->mini_map.line_length,
	// 		&game->mini_map.endian);
}


//camera plane is the fov
//dir is the direction the player is facing
/*Draw your FOV as a triangle:

    Wide base (big plane): covers more map, so objects look smaller and the edge is closer.
    Narrow base (small plane): covers less map, so objects look bigger and the edge is farther.
*/
static void	player_init(t_game *game)
{
	game->player.posx = 3.5;
	game->player.posy = 7.5;
	game->player.dirx = 0;
	game->player.diry = -1;
	game->player.planey = 0;
	game->player.planex = 0.66;
}



/*->dir its the direction, like if dirx = 1 & diry = 0, we are looking rigth
  ->plane is a perpendicular vector to the direction, it determines the FOV.
  ->camerax indicates how much the ray is leaning to the left/rigth(valors go between [-1,1])
  ->raydir are the vector that when added will give me the ray,so basicly camra x tells me wich side the ray is
  the math to get raydirx/y is basicly connecting the the player the pointy part of the triangle
  to the base,using the direction he is looking, the fov, and how far left or rigth the ray should be*/
void setup_ray(t_game *game, int x)
{
    game->meth.camerax = 2 * x / (double)WIDTH - 1;
    game->meth.raydirx = game->player.dirx + game->player.planex * game->meth.camerax;
    game->meth.raydiry = game->player.diry + game->player.planey * game->meth.camerax;
    game->meth.mapx = (int)game->player.posx;
    game->meth.mapy = (int)game->player.posy;
}

/*->so here, if raydir is 0 means we are following the x/y axes, and since we cant divide by 0 we just slap a big ahh number
   cuz point the square of our grid is 1 by 1,and we are calculating how far we need to go to reach the other line
   (vertical on raydirx other way around on y) we use fabs because it cant be negative since its a distance
   ->so deltacalculates how far each square is from eachother following the ray, sidedis calculates how far the player is
   from the closes line, since the player can be in a lot of diferent places in the same square since we use floats to walk around
    ->step is just the directions the ray is going*/
void prepare_dda(t_game *game)
{
    if (game->meth.raydirx == 0)
        game->meth.deltadistx = 1e30;
    else
        game->meth.deltadistx = fabs(1 / game->meth.raydirx);
    if (game->meth.raydiry == 0)
        game->meth.deltadisty = 1e30;
    else
        game->meth.deltadisty = fabs(1 / game->meth.raydiry);

    if (game->meth.raydirx < 0)
    {
        game->meth.stepx = -1;
        game->meth.sidedistx = (game->player.posx - game->meth.mapx) * game->meth.deltadistx;
    }
    else
    {
        game->meth.stepx = 1;
        game->meth.sidedistx = (game->meth.mapx + 1.0 - game->player.posx) * game->meth.deltadistx;
    }
    if (game->meth.raydiry < 0)
    {
        game->meth.stepy = -1;
        game->meth.sidedisty = (game->player.posy - game->meth.mapy) * game->meth.deltadisty;
    }
    else
    {
        game->meth.stepy = 1;
        game->meth.sidedisty = (game->meth.mapy + 1.0 - game->player.posy) * game->meth.deltadisty;
    }
}
/*->hit wall we calculate how far the ray goes until it hits a wall, so we need to add the distance the player need to reach the closes wall
   then we just nned to add delta,because its the distance the ray walsk to go from one line to another lane in the same orientation(x or y)
  ->we add on the map side, because we need to "walk" on the map to be able to identify the wall*/

int	hit_wall(t_game *game)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (game->meth.sidedistx < game->meth.sidedisty)
		{
			game->meth.sidedistx += game->meth.deltadistx;
			game->meth.mapx += game->meth.stepx;
			side = 0;
		}
		else
		{
			game->meth.sidedisty += game->meth.deltadisty;
			game->meth.mapy += game->meth.stepy;
			side = 1;
		}
		if (game->map[game->meth.mapy][game->meth.mapx] >= '1')
			hit = 1;
	}
	return (side);
}

/*this is jsut becayse the DDA walks one square 2 much so we gotta go back one square to get the real distance*/
double calc_wall_dist(t_game *game)
{
    if (game->meth.orientation == 0)
        return game->meth.sidedistx - game->meth.deltadistx;
    else
        return game->meth.sidedisty - game->meth.deltadisty;
}


/*->after knowing how far the wall is, i will divide the how tall my screen is by the distance
   if the distance is small, means im close when i divide a big number by a small number i get a big number
   so the line heigh will be nig, i will draw more pixels, big wall
   ->here the minus symbol menas go up, so to draw the wall i will go to the middle of the screen,
   then go up half of the size of the wall and mark that pixel,the do the same to the lower half
   so i know when to stop the wall*/
void	wall_size(t_game *game, double walldist, int *sdraw, int *edraw)
{
	int	line_heigth;

	(void)game;
	if (walldist <= 0.000001)
		walldist = 0.000001;
	line_heigth = (int)(HEIGHT / walldist);
	(*sdraw) = -line_heigth / 2 + HEIGHT / 2;
	if ((*sdraw) < 0)
		(*sdraw) = 0;
	(*edraw) = line_heigth / 2 + HEIGHT / 2;
	if ((*edraw) < 0)
		(*edraw) = 0;
}
/*->here now that i have the the heigth of the wall, i start drawing from above,so unitl
   sdraw i draw the ceiling, when i reach sdraw and until i reach edraw i will draw the wall
   then i just finish with the floor coolor*/
void	artistic_moment(t_game *game, int x, int sdraw, int edraw)
{
	int	color;
	int	ceiling;
	int	floor;
	int	y;

	ceiling = 0x0000FF;
	floor = 0xFFA500;
	y = 0;
	if (game->meth.orientation == 0)
		color = 0xFF0000;
	else
		color = 0x880000;
	while (y < HEIGHT)
	{
		if (y < sdraw)
			my_mlx_pixel_put(&game->bg_img, x, y, ceiling);
		else if (y >= sdraw && y <= edraw)
			my_mlx_pixel_put(&game->bg_img, x, y, color);
		else
			my_mlx_pixel_put(&game->bg_img, x, y, floor);
		y++;
	}
}
void	math_with_an_e(t_game *game)
{
	int		i;
	double	walldist;
	int		sdraw;
	int		edraw;

	i = 0;
	while (i < WIDTH)
	{
		setup_ray(game,i);
		prepare_dda(game);
		game->meth.orientation = hit_wall(game);
		walldist = calc_wall_dist(game);
		wall_size(game, walldist, &sdraw, &edraw);
		artistic_moment(game, i, sdraw, edraw);
		i++;
	}
}
void	map_gen(t_game *game)
{
	player_init(game);
	background_gen(game);
	math_with_an_e(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
}