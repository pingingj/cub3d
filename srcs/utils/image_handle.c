/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:28:51 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/05 16:54:03 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	make_fade_screen(t_game *game, t_img *img)
{
	static double	i;
	t_point			scale;
	t_img			*scaled;

	scale.x = WIDTH;
	scale.y = HEIGHT;
	mlx_mouse_show(game->mlx, game->win);
	if (i > 1.5)
		game->g_flags.game_state = Finished;
	scaled = draw_scaled_img(game, img, scale, i);
	if (scaled == NULL)
		print_errors(game, 2, "New img failed");
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, scaled->img, 0, 0);
	mlx_destroy_image(game->mlx, scaled->img);
	free(scaled);
	i += 0.01;
}

void	make_pause_screen(t_game *game)
{
	t_point	scale;
	t_img	*scaled;

	scale.x = WIDTH;
	scale.y = HEIGHT;
	if (game->g_flags.game_state == Pause)
	{
		scaled = draw_scaled_img(game, &game->ass.pause_screen, scale, -1);
		if (scaled == NULL)
			print_errors(game, 2, "New img failed");
		mlx_clear_window(game->mlx, game->win);
		mlx_put_image_to_window(game->mlx, game->win, scaled->img, 0, 0);
		mlx_destroy_image(game->mlx, scaled->img);
		free(scaled);
	}
}
