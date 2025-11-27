/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:28:51 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/27 19:03:45 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	new_blank_img(t_game *game, t_img *img, int w, int h)
{
	img->img = mlx_new_image(game->mlx, w, h);
	if (!img->img)
		return (0);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(game->mlx, img->img);
		img->img = NULL;
		return (0);
	}
	img->w = w;
	img->h = h;
	img->filename = NULL;
	return (1);
}

void	scale_img_loop(t_img *src, double intensity, t_game *game, t_img *dst)
{
	game->scaling.s_xy.y = (long long)game->scaling.xy.y * src->h / dst->h;
	if (game->scaling.s_xy.y >= src->h)
		game->scaling.s_xy.y = src->h - 1;
	game->scaling.dst_row = (unsigned char *)dst->addr + game->scaling.xy.y
		* dst->line_length;
	game->scaling.src_row = (unsigned char *)src->addr + game->scaling.s_xy.y
		* src->line_length;
	game->scaling.xy.x = 0;
	while (game->scaling.xy.x < dst->w)
	{
		game->scaling.s_xy.x = (long long)game->scaling.xy.x * src->w / dst->w;
		if (game->scaling.s_xy.x >= src->w)
			game->scaling.s_xy.x = src->w - 1;
		game->scaling.rgba[2] = game->scaling.src_row[game->scaling.s_xy.x
			* game->scaling.s_bpp + 0];
		game->scaling.rgba[1] = game->scaling.src_row[game->scaling.s_xy.x
			* game->scaling.s_bpp + 1];
		game->scaling.rgba[0] = game->scaling.src_row[game->scaling.s_xy.x
			* game->scaling.s_bpp + 2];
		game->scaling.rgba[3] = game->scaling.src_row[game->scaling.s_xy.x
			* game->scaling.s_bpp + 3];
		game->scaling.color = (game->scaling.rgba[0] << 16) | (game->scaling.rgba[1] << 8) | game->scaling.rgba[2];
		if (intensity >= 0)
			game->scaling.color = add_light(game->scaling.color, intensity);
		game->scaling.dst_row[game->scaling.xy.x * game->scaling.d_bpp
			+ 0] = game->scaling.color & 0xFF;
		game->scaling.dst_row[game->scaling.xy.x * game->scaling.d_bpp
			+ 1] = (game->scaling.color >> 8) & 0xFF;
		game->scaling.dst_row[game->scaling.xy.x * game->scaling.d_bpp
			+ 2] = (game->scaling.color >> 16) & 0xFF;
		game->scaling.dst_row[game->scaling.xy.x * game->scaling.d_bpp
			+ 3] = game->scaling.rgba[3];
		game->scaling.xy.x++;
	}
}
void	scale_img(t_img *src, double intensity, t_img *dst, t_game *game)
{
	game->scaling.s_bpp = src->bits_per_pixel / 8;
	game->scaling.d_bpp = dst->bits_per_pixel / 8;
	while (game->scaling.xy.y < dst->h)
	{
		scale_img_loop(src, intensity, game, dst);
		game->scaling.xy.y++;
	}
}
t_img	*draw_scaled_img(t_game *game, t_img *src, t_point scale,
		double intensity)
{
	t_img	*dst;

	ft_bzero(&game->scaling, sizeof(game->scaling));
	if (!game || !src || !src->img || !src->addr || src->w <= 0 || src->h <= 0)
		return (NULL);
	dst = ft_calloc(1, sizeof(t_img));
	if (!dst)
		return (NULL);
	if (!new_blank_img(game, dst, scale.x, scale.y))
		return (free(dst), NULL);
	scale_img(src, intensity, dst, game);
	return (dst);
}

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
		mlx_clear_window(game->mlx, game->win);
		mlx_put_image_to_window(game->mlx, game->win, scaled->img, 0, 0);
		mlx_destroy_image(game->mlx, scaled->img);
		free(scaled);
	}
}
