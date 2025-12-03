/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:07:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/03 15:23:21 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	coin_pos(t_game *game)
{
	int	x;
	int	y;
	int	index;

	y = -1;
	index = 0;
	game->ass.sprites = ft_calloc(game->ass.collect_amount + 1,
			sizeof(t_sprite));
	if (game->ass.sprites == NULL)
		print_errors(game, 1, "Failed malloc in spritess");
	while (++y < game->map.pos.y)
	{
		x = -1;
		while (game->map.grid[y][++x])
		{
			if (game->map.grid[y][x] == 'c')
			{
				game->ass.sprites[index].enemy = false;
				game->ass.sprites[index].exists = true;
				game->ass.sprites[index].cords.x = x + 0.5;
				game->ass.sprites[index].cords.y = y + 0.5;
				index++;
			}
		}
	}
}

void	make_sprites_aux(t_game *game, int amount)
{
	game->ass.collect_amount = amount + 1;
	if (amount > 0)
		game->g_flags.collectibles_exist = true;
	if (amount > 0 && !game->ass.textures[CL].filename)
		print_errors(game, 1, "Missing collectible texutre");
	if (amount > 8)
		print_errors(game, 1, "Too many collectibles (max 8)");
	coin_pos(game);
}

void	make_sprites(t_game *game)
{
	int	x;
	int	y;
	int	amount;

	amount = 0;
	y = 0;
	while (y < game->map.pos.y)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'C')
				print_errors(game, 1, "Unreachable collectible found");
			if (game->map.grid[y][x] == 'c')
				amount++;
			x++;
		}
		y++;
	}
	make_sprites_aux(game, amount);
	if (game->ass.enemy.cords.x != -1)
	{
		game->ass.sprites[amount].exists = true;
		game->ass.sprites[amount].enemy = true;
	}
}

bool	parse(t_game *game, char *filename)
{
	char	*line;

	init_vars(game);
	game->fd = open(filename, O_RDONLY);
	if (game->fd == -1)
		print_errors(game, 0, "Invalid file or no file provided");
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
		print_errors(game, 0, "File is not in the correct format");
	line = get_textures(game);
	if (!game->ass.ceiling.nums || !game->ass.floor.nums
		|| !game->ass.textures[NO].filename || !game->ass.textures[EA].filename
		|| !game->ass.textures[WE].filename || !game->ass.textures[SO].filename)
	{
		free(line);
		print_errors(game, 1, "Missing texture or color");
	}
	parse_map(game, filename, line);
	parse_colors(game);
	close(game->fd);
	make_enemy(game);
	make_sprites(game);
	return (true);
}
