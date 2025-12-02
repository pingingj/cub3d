/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:40:28 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/02 13:31:44 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	ft_sleep(double mili_secs)
{
	double			last_time;
	struct timeval	now;
	double			current_time;

	last_time = 0.0;
	if (mili_secs <= 0.0)
		return ;
	gettimeofday(&now, NULL);
	current_time = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
	if (last_time == 0.0)
		last_time = current_time;
	while (1)
	{
		gettimeofday(&now, NULL);
		current_time = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
		if (current_time - last_time >= mili_secs)
			break ;
	}
}

void	lock_fps_math(t_game *game, struct timeval *now, double *fsleep)
{
	double			target_ms;
	double			now_ms;
	static double	next_deadline_ms;

	if (game->fps_lock > 0)
	{
		target_ms = 1000.0 / (double)game->fps_lock;
		gettimeofday(now, NULL);
		now_ms = (now->tv_sec * 1000.0) + (now->tv_usec / 1000.0);
		if (next_deadline_ms == 0.0)
			next_deadline_ms = now_ms + target_ms;
		(*fsleep) = next_deadline_ms - now_ms;
		if ((*fsleep) < 0.0)
			(*fsleep) = 0.0;
		next_deadline_ms += target_ms;
		if (next_deadline_ms < now_ms - target_ms)
			next_deadline_ms = now_ms + target_ms;
	}
	else
		next_deadline_ms = 0.0;
}

double	fps_counter(t_game *game)
{
	static int		frames;
	struct timeval	now;
	static double	last_time;
	double			current_time;
	double			fsleep;

	fsleep = 0.0;
	lock_fps_math(game, &now, &fsleep);
	gettimeofday(&now, NULL);
	current_time = now.tv_sec + now.tv_usec / 1000000.0;
	if (last_time == 0.0)
		last_time = current_time;
	frames++;
	if (current_time - last_time >= 1.0)
	{
		printf("fps = %d\n", frames);
		frames = 0;
		last_time = current_time;
	}
	return (fsleep);
}
