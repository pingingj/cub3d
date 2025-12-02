/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:15 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 17:57:37 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	background_gen(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "NEETs");
	if (!game->win)
	{
		ft_printf("New window failed [!]\n");
		exit(1);
	}
	game->bg_img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->bg_img.img)
	{
		ft_printf("background creation failed [!]\n");
		exit(1);
	}
	game->bg_img.addr = mlx_get_data_addr(game->bg_img.img,
			&game->bg_img.bits_per_pixel, &game->bg_img.line_length,
			&game->bg_img.endian);
	if (!game->bg_img.addr)
	{
		ft_printf("background adress failed [!]\n");
		exit(1);
	}
}

// camera plane is the fov
// dir is the direction the player is facing
/*Draw your FOV as a triangle:

	Wide base (big plane): covers more map,
		so objects look smaller and the edge is closer.
	Narrow base (small plane): covers less map,
		so objects look bigger and the edge is farther.
*/

int	add_light(int color, double intensity)
{
	int	red;
	int	green;
	int	blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	red = (int)(red * intensity);
	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;
	green = (int)(green * intensity);
	if (green > 255)
		green = 255;
	if (green < 0)
		green = 0;
	blue = (int)(blue * intensity);
	if (blue > 255)
		blue = 255;
	if (blue < 0)
		blue = 0;
	return ((red << 16) | (green << 8) | blue);
}

void	map_gen(t_game *game)
{
	game->player.speed = MOVE_SPEED;
	background_gen(game);
	create_frame(game);
}
