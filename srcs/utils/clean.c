/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:55:00 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/19 18:22:13 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	closex(t_game *mlx)
{
	ft_printf("\n\nGAME CLOSING\n");
    // mlx_destroy_image(mlx->mlx,mlx->bg_img.img);
	mlx_destroy_image(mlx->mlx,mlx->mini_map.img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}