/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/25 18:22:18 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	main(int argc, char **argv)
{
	t_game game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
	{
		print_errors(&game, 1, "Not valid amount of arguments");
		return (1);
	}
	if (parse(&game, argv[1]) == false)
		return (1);
	printf("NO = %s\n", game.ass.walls[NO].filename);
	printf("EA = %s\n", game.ass.walls[EA].filename);
	printf("SO = %s\n", game.ass.walls[SO].filename);
	printf("WE = %s\n", game.ass.walls[WE].filename);
	printf("Ceiling = %s\n", game.ass.ceiling.nums);
	printf("R = %d\n", game.ass.ceiling.red);
	printf("G = %d\n", game.ass.ceiling.green);
	printf("B = %d\n", game.ass.ceiling.blue);
	printf("Floor = %s\n", game.ass.floor.nums);
	printf("R = %d\n", game.ass.floor.red);
	printf("G = %d\n", game.ass.floor.green);
	printf("B = %d\n", game.ass.floor.blue);
	printf("hexa ceiling = %d\n", game.ass.ceiling.hexa);
	printf("hexa floor = %d\n", game.ass.floor.hexa);
	print_map(game.map);
	free_game(&game);
	return (0);
}