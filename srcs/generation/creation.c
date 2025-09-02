/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:15 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/28 15:27:06 by dpaes-so         ###   ########.fr       */
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
	game->mini_map.img = mlx_new_image(game->mlx, 300, 300);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.img,
			&game->mini_map.bits_per_pixel, &game->mini_map.line_length,
			&game->mini_map.endian);
}

// camera plane is the fov
// dir is the direction the player is facing
/*Draw your FOV as a triangle:

	Wide base (big plane): covers more map,
		so objects look smaller and the edge is closer.
	Narrow base (small plane): covers less map,
		so objects look bigger and the edge is farther.
*/
static void	player_init(t_game *game)
{
	game->player.speed = MOVE_SPEED;
}

int add_light(int color,double intensity)
{
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;

    // Apply light and clamp
    red = (int)(red * intensity);
    if (red > 255) red = 255;
    if (red < 0) red = 0;

    green = (int)(green * intensity);
    if (green > 255) green = 255;
    if (green < 0) green = 0;

    blue = (int)(blue * intensity);
    if (blue > 255) blue = 255;
    if (blue < 0) blue = 0;

    // Repack to hex integer
    return (red << 16) | (green << 8) | blue;
}

/*okay here is another tricky one,softeness is the bwam radius and how soft it is gonna be
	ambient is the darkest is gonna be, 1 is the brigthetest,i use exp to calculate based on
	the distance to the center how far or close to the center is,then i use the distance to the wall,
	and the max reach of the flashlight to calculate how bright again it need to be,
	then i use the ambient that is how dark the defualt world is to calculate using how close to the
	center of the bam and how close to a wall how dark the pixel needs to be, aka intenisty then i jsut multyply
	that on the mypixelput color*/
double flashlight(int x,int y, t_game *game)
{
	double intensity;
	double dist_intensity;
	double max_dist;
	double circ_intensity;
	double softness;
	double dx;
	double dy;
	double dist;

    dx = x - WIDTH / 2;
    dy = y - HEIGHT / 2;
    softness = 200.0;
    max_dist = 7.0; // Controls how far the beam reaches
    dist = sqrt(dx * dx + dy * dy);
    circ_intensity = exp(-((dist * dist) / (2 * softness * softness)));
    dist_intensity = 1.0 - (game->walldist / max_dist);
    if (dist_intensity < 0.0)
		dist_intensity = 0.0;
    intensity = AMBIENT + (1.0 - AMBIENT) * circ_intensity * dist_intensity;
	 if (intensity < AMBIENT)
		intensity = AMBIENT;
    if (intensity > 1.0)
		intensity = 1.0;
	return(intensity);
}
/*->here now that i have the the heigth of the wall,
	i start drawing from above,so unitl
   sdraw i draw the ceiling,
	when i reach sdraw and until i reach edraw i will draw the wall
   then i just finish with the floor coolor*/
void artistic_moment(t_game *game, int x, int sdraw, int edraw)
{
    int color;
    int door;
    int y;
	double intensity;

    if (game->meth.orientation == 0)
        color = 0x0000FF;
    else
        color = 0x0000DF;
    if (game->meth.orientation == 0)
        door = 0x964B00;
    else
        door = 0x964B90;
    y = 0;
    while (y < HEIGHT)
    {
		intensity = flashlight(x,y,game);
        if (y < sdraw)
            my_mlx_pixel_put(&game->bg_img, x, y, add_light(game->ass.ceiling.hexa, AMBIENT + 0.07));
        else if (y >= sdraw && y <= edraw && game->meth.door == false)
            my_mlx_pixel_put(&game->bg_img, x, y, add_light(color, intensity));
        else if (y >= sdraw && y <= edraw && game->meth.door == true)
            my_mlx_pixel_put(&game->bg_img, x, y, add_light(door, intensity));
        else
            my_mlx_pixel_put(&game->bg_img, x, y, add_light(game->ass.floor.hexa, AMBIENT + 0.07));
        y++;
    }
}

void	map_gen(t_game *game)
{
	game->move = ft_calloc(7, sizeof(int));
	if (!game->move)
		exit(1);
	printf("x = %f   y = %f\n",game->player.posx,game->player.posy);
	player_init(game);
	background_gen(game);
	create_frame(game);
}
