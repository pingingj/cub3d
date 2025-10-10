/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:54:55 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/09 16:51:02 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	textures(t_game *game)
{
	game->ass.barrel.img = mlx_xpm_file_to_image(game->mlx,
			"incs/textures/barrel.xpm", &game->ass.barrel.w,
			&game->ass.barrel.h);
	game->ass.barrel.addr = mlx_get_data_addr(game->ass.barrel.img,
			&game->ass.barrel.bits_per_pixel,
			&game->ass.barrel.line_length,
			&game->ass.barrel.endian);
	return (1);
}
