/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:54:55 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/02 17:15:34 by dpaes-so         ###   ########.fr       */
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
	
	//hard code
	game->ass.collect_amount = 2;
	game->ass.collectible = ft_calloc(game->ass.collect_amount,sizeof(t_sprite));
	game->ass.collectible[0].cords.x = 19.5;
	game->ass.collectible[0].cords.y = 17.5;
	game->ass.collectible[1].cords.x = 21.5;
	game->ass.collectible[1].cords.y = 17.5;
	//hard code
	return (1);
}
