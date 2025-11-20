/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:50:26 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/20 16:07:08 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	move_monster(double speed, t_game *game, t_pos d, double dist)
{
	t_pos	move;

	move.x = game->ass.enemy.cords.x + speed * (d.x / dist);
	move.y = game->ass.enemy.cords.y + speed * (d.y / dist);
	if (game->map.grid[(int)move.y][(int)move.x] != '1'
		&& game->map.grid[(int)move.y][(int)move.x] != 'd')
	{
		game->ass.enemy.cords.x = move.x;
		game->ass.enemy.cords.y = move.y;
		game->ass.sprites[game->ass.collect_amount
			- 1].cords.x = game->ass.enemy.cords.x;
		game->ass.sprites[game->ass.collect_amount
			- 1].cords.y = game->ass.enemy.cords.y;
	}
}
int	monster(t_game *game)
{
	t_pos	target;
	t_pos	d;
	double	dist;
	double	speed;
	bool	step_monster;

	target.x = 0;
	target.y = 0;
	choose_pathfinding_alg(game, target, &d, &step_monster);
	if (step_monster == false)
		return (0);
	dist = sqrt(d.x * d.x + d.y * d.y);
	if (game->g_flags.collectibles_exist && game->ass.collect_amount
		- 1 != game->collected_comics)
		speed = (MONSTER_SPEED / ((game->ass.collect_amount - 1)
					- game->collected_comics));
	else
		speed = 0.09;
	if (dist > 0.5)
		move_monster(speed, game, d, dist);
	else
		game->g_flags.game_state = death_screen;
	return (0);
}
