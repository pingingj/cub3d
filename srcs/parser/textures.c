/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:54:55 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/16 15:32:57 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	img_init(t_game *game, char *filename, t_img *img)
{
	img->img = mlx_xpm_file_to_image(game->mlx,
			filename, &img->w,
			&img->h);
	if (img->img == NULL)
		print_errors(game, 1, "Failed to use xpm file", -1);
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
	if (img->addr == NULL)
		print_errors(game, 1, "Failed to use xpm file", -1);
}

int	textures(t_game *game)
{
	img_init(game, "incs/textures/barrel.xpm", &game->ass.barrel);
	img_init(game, game->ass.walls[NO].filename, &game->ass.walls[NO]);
	img_init(game, game->ass.walls[EA].filename, &game->ass.walls[EA]);
	img_init(game, game->ass.walls[WE].filename, &game->ass.walls[WE]);
	img_init(game, game->ass.walls[SO].filename, &game->ass.walls[SO]);
	// game->ass.walls[]
	return (1);
}
