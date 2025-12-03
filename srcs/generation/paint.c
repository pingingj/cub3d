/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:14:15 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/03 19:04:04 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	paint_exe(t_game *game, int x, int y, int color)
{
	double	intensity;
	bool	flag;

	if (color == game->ass.floor.hexa)
		flag = false;
	else
		flag = true;
	if (color == game->ass.ceiling.hexa)
	{
		if (game->g_flags.laggy_lantern)
			my_mlx_pixel_put(&game->bg_img, x, y, add_light(color, AMBIENT
					+ 0.07));
		else
			my_mlx_pixel_put(&game->bg_img, x, y, color);
		return ;
	}
	if (game->g_flags.laggy_lantern)
	{
		intensity = flashlight(x, y, game, flag);
		my_mlx_pixel_put(&game->bg_img, x, y, add_light(color, intensity));
	}
	else
		my_mlx_pixel_put(&game->bg_img, x, y, color);
}

void	texture_x_pos(t_game *game, t_img *sprite, t_point *text, double wallx)
{
	if (game->meth.orientation == 0 && game->meth.raydirx < 0)
	{
		(*sprite) = game->ass.textures[WE];
		text->x = (int)(wallx * (double)sprite->w);
		text->x = sprite->w - text->x - 1;
	}
	else if (game->meth.orientation == 0 && game->meth.raydirx > 0)
	{
		(*sprite) = game->ass.textures[EA];
		text->x = (int)(wallx * (double)sprite->w);
	}
	else if (game->meth.orientation == 1 && game->meth.raydiry > 0)
	{
		(*sprite) = game->ass.textures[SO];
		text->x = (int)(wallx * (double)sprite->w);
		text->x = sprite->w - text->x - 1;
	}
	else
	{
		(*sprite) = game->ass.textures[NO];
		text->x = (int)(wallx * (double)sprite->w);
	}
}

static double	wallx(t_game *game)
{
	double	wallx;

	if (game->meth.orientation == 0)
		wallx = game->player.posy + game->walldist * game->meth.raydiry;
	else
		wallx = game->player.posx + game->walldist * game->meth.raydirx;
	wallx -= floor(wallx);
	return (wallx);
}

int	get_color(t_game *game, int sdraw, int y)
{
	t_point	text;
	int		color;
	t_pos	textpos;
	char	*pixel;
	t_img	sprite;

	texture_x_pos(game, &sprite, &text, wallx(game));
	if (game->meth.door == true)
	{
		sprite = game->ass.door.texture;
		text.x = (int)(wallx(game) * (double)sprite.w);
	}
	textpos.x = (sdraw - (int)((HEIGHT / 2) + (game->player.look + game->bob))
			+ game->meth.line_height / 2) * (1.0 * sprite.h
			/ game->meth.line_height);
	textpos.y = textpos.x + (y - sdraw) * (1.0 * sprite.h
			/ game->meth.line_height);
	text.y = (int)textpos.y % (sprite.h);
	pixel = sprite.addr + (text.y * sprite.line_length + text.x
			* (sprite.bits_per_pixel / 8));
	color = *(int*)pixel;
	return (color);
}

/*->here now that i have the the heigth of the wall,
	i start drawing from above,so unitl
   sdraw i draw the ceiling,
	when i reach sdraw and until i reach edraw i will draw the wall
   then i just finish with the floor coolor*/
void	artistic_moment(t_game *game, int x, int sdraw, int edraw)
{
	int	color;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		if ((x > game->mini.offset && x < game->mini.offset + game->mini.size.x)
			&& (y > game->mini.offset && y < game->mini.offset
				+ game->mini.size.y) && game->mini.show == true)
			continue ;
		if (y < sdraw)
			paint_exe(game, x, y, game->ass.ceiling.hexa);
		else if (y >= sdraw && y <= edraw && game->meth.door == false)
		{
			color = get_color(game, sdraw, y);
			paint_exe(game, x, y, color);
		}
		else if (y >= sdraw && y <= edraw && game->meth.door == true)
		{
			color = get_color(game, sdraw, y);
			paint_exe(game, x, y, color);
		}
		else
			paint_exe(game, x, y, game->ass.floor.hexa);
	}
}
