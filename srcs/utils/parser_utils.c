/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:01:42 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/11/26 19:02:11 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

char	**letters_init(void)
{
	static char	*letters[7];

	letters[NO] = "NO ";
	letters[EA] = "EA ";
	letters[WE] = "WE ";
	letters[SO] = "SO ";
	letters[CL] = "CL ";
	letters[EN] = "EN ";
	letters[DO] = "DO ";
	return (letters);
}

void	init_vars(t_game *game)
{
	game->mini.tile_size = 60;
	game->mini.show = true;
	game->g_flags.laggy_lantern = true;
	game->player.posx = -1;
	game->player.posy = -1;
	game->player.look = 0;
}
