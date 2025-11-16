/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:54:55 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/20 18:45:24 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	img_init(t_game *game, char *filename, t_img *img)
{
	img->img = mlx_xpm_file_to_image(game->mlx,
			filename, &img->w,
			&img->h);
	if (img->img == NULL)
	{
		printf("Failed to use xpm file\n");
		closex(game);
	}
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
	if (img->addr == NULL)
	{
		printf("Failed to use xpm file\n");
		closex(game);
	}		
}

int	textures(t_game *game)
{
	int		i;
	char	*filename;
	char	*path;
	char	*num;

	i = 0;
	while(i < 194)
	{
		path = "./incs/textures/titlescreen/";
		// printf("i = %d\n", i);
		num = ft_itoa(i);
		filename = ft_strjoin(path, num);
		free(num);
		filename = ft_strjoin2(filename, ".xpm");
		// printf("filename = %s\n", filename);
		img_init(game, filename, &game->title[i]);
		free(filename);
		i++;
	}
	img_init(game, game->ass.textures[NO].filename, &game->ass.textures[NO]);
	img_init(game, game->ass.textures[EA].filename, &game->ass.textures[EA]);
	img_init(game, game->ass.textures[WE].filename, &game->ass.textures[WE]);
	img_init(game, game->ass.textures[SO].filename, &game->ass.textures[SO]);
	if (game->ass.textures[CL].filename)
		img_init(game, game->ass.textures[CL].filename, &game->ass.textures[CL]);
	if (game->ass.textures[EN].filename)
		img_init(game, game->ass.textures[EN].filename, &game->ass.enemy.texture);
	if (game->ass.textures[DO].filename)
		img_init(game, game->ass.textures[DO].filename, &game->ass.door.texture);
	return (1);
}
