/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:54:55 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/25 17:41:05 by dgarcez-         ###   ########.fr       */
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
		ft_dprintf(2, "Error\nFailed to use %s file\n", filename);
		closex(game);
	}
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
	if (img->addr == NULL)
	{
		ft_dprintf(2, "Error\nFailed to use %s file\n", filename);
		closex(game);
	}
}

void	set_num_imgs(t_game *game)
{
	img_init(game, "./incs/textures/nums/zero.xpm", &game->nums[0]);
	img_init(game, "./incs/textures/nums/one.xpm", &game->nums[1]);
	img_init(game, "./incs/textures/nums/two.xpm", &game->nums[2]);
	img_init(game, "./incs/textures/nums/three.xpm", &game->nums[3]);
	img_init(game, "./incs/textures/nums/four.xpm", &game->nums[4]);
	img_init(game, "./incs/textures/nums/five.xpm", &game->nums[5]);
	img_init(game, "./incs/textures/nums/six.xpm", &game->nums[6]);
	img_init(game, "./incs/textures/nums/seven.xpm", &game->nums[7]);
	img_init(game, "./incs/textures/nums/eight.xpm", &game->nums[8]);
}

void	bonus_init(t_game *game, bool collectible, char *enemy, char *door)
{
	if (game->ass.textures[CL].filename)
		img_init(game, game->ass.textures[CL].filename,
			&game->ass.textures[CL]);
	if (collectible == true)
	{
		img_init(game, "./incs/textures/Win_screen.xpm", &game->ass.win_screen);
		img_init(game, "./incs/textures/nums/slash.xpm", &game->slash);
		set_num_imgs(game);
	}
	if (enemy)
		img_init(game, enemy, &game->ass.enemy.texture);
	if (door)
		img_init(game, door, &game->ass.door.texture);
}

void	menu_init(t_game *game)
{
	int		i;
	char	*filename;
	char	*path;
	char	*num;

	i = 0;
	while (i < 194)
	{
		path = "./incs/textures/titlescreen/";
		num = ft_itoa(i);
		filename = ft_strjoin(path, num);
		free(num);
		filename = ft_strjoin2(filename, ".xpm");
		img_init(game, filename, &game->title[i]);
		free(filename);
		i++;
	}
}

int	textures(t_game *game)
{
	img_init(game, game->ass.textures[NO].filename, &game->ass.textures[NO]);
	img_init(game, game->ass.textures[EA].filename, &game->ass.textures[EA]);
	img_init(game, game->ass.textures[WE].filename, &game->ass.textures[WE]);
	img_init(game, game->ass.textures[SO].filename, &game->ass.textures[SO]);
	// img_init(game, "./incs/textures/Fusuma1.xpm", &game->door_frames[0]);
	// img_init(game, "./incs/textures/Fusuma2.xpm", &game->door_frames[1]);
	// img_init(game, "./incs/textures/Fusuma3.xpm", &game->door_frames[2]);
	// img_init(game, "./incs/textures/Fusuma4.xpm", &game->door_frames[3]);
	img_init(game, "./incs/textures/death_screen.xpm", &game->ass.death_screen);
	img_init(game, "./incs/textures/pause.xpm", &game->ass.pause_screen);
	bonus_init(game, game->g_flags.collectibles_exist,
		game->ass.textures[EN].filename, game->ass.textures[DO].filename);
	menu_init(game);
	return (1);
}
