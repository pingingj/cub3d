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

/*->here now that i have the the heigth of the wall,
	i start drawing from above,so unitl
   sdraw i draw the ceiling,
	when i reach sdraw and until i reach edraw i will draw the wall
   then i just finish with the floor coolor*/
void	artistic_moment(t_game *game, int x, int sdraw, int edraw)
{
	int	color;
	int	ceiling;
	int	floor;
	int door;
	int	y;

	ceiling = game->ass.ceiling.hexa;
	floor = game->ass.floor.hexa;
	y = 0;
	if (game->meth.orientation == 0)
		color = 0x0000FF;
	else
		color = 0x0000DF;
	if (game->meth.orientation == 0)
		door = 0x964B00;
	else
		door = 0x964B90;
	while (y < HEIGHT)
	{
		if (y < sdraw)
			my_mlx_pixel_put(&game->bg_img, x, y, ceiling);
		else if (y >= sdraw && y <= edraw && game->meth.door == false)
			my_mlx_pixel_put(&game->bg_img, x, y, color);
		else if (y >= sdraw && y <= edraw && game->meth.door == true)
			my_mlx_pixel_put(&game->bg_img, x, y, door);
		else
			my_mlx_pixel_put(&game->bg_img, x, y, floor);
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
