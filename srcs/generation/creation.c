/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:15 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/19 18:20:58 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	background_gen(t_game *game)
{
	game->win = mlx_new_window(game->mlx, 1920, 1080, "NEETs");
	// game->bg_img.img = mlx_new_image(game->mlx, 1920, 1080);
	// game->bg_img.addr = mlx_get_data_addr(game->bg_img.img,
	// 		&game->bg_img.bits_per_pixel, &game->bg_img.line_length,
	// 		&game->bg_img.endian);
	game->mini_map.img = mlx_new_image(game->mlx, 200, 200);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.img,
			&game->mini_map.bits_per_pixel, &game->mini_map.line_length,
			&game->mini_map.endian);
}
void	map_gen(t_game *game)
{
	background_gen(game);
}